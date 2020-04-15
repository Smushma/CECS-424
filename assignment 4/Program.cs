using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Linq;

namespace Lab4
{
	class Program
	{
		/**
		 * Directory/File crawler
		 */
		private static IEnumerable<string> EnumerateFilesRecursively(string path)
		{
			foreach (string dir in Directory.EnumerateDirectories(path)) 
			{
				foreach (string file in Directory.EnumerateFiles(dir))
				{
					yield return file;
				}

				// Look though all sub directories
				EnumerateFilesRecursively(dir);
			}
		}		

		/**
		 * Format to human readable format for:
		 * B, kB, MB, GB, TB, PB, EB, and ZB 
		 * (Longs run out around EB)
		 */
		private static string FormatByteSize(long byteSize)
		{
			string[] sizeSuffixes = {
				"B",
				"kB",
				"MB",
				"GB",
				"TB",
				"PB",
				"EB",
				"ZB"
			};

			// Base case for 0 byte size
			if (byteSize == 0) 
				return "0" + sizeSuffixes[0];

			// Handle negative sizes
			long bytes = Math.Abs(byteSize);
			// Determine the # of decimal places in base 1000
			int place = Convert.ToInt32(Math.Floor(Math.Log(bytes, 1000)));
			// Divide by 1000^decimal places and round to 2 decimal places
			double num = Math.Round(bytes / Math.Pow(1000, place), 2); 

			return (Math.Sign(byteSize) * num).ToString() + sizeSuffixes[place]; 
		}

		/**
		 * Creates a HTML report file
		 */
		private static XDocument CreateReport(IEnumerable<string> files)
			=> new XDocument(
				new XDocumentType("html", null, null, null),
				new XElement("html",
					new XElement("head",
						new XElement("title", "File Report"),
						new XElement("style", "table, th, td { border: 1px solid black; }")
					),
					new XElement("body",
						new XElement("table",
							new XAttribute("border", "1"),
								new XElement("thead",
									new XElement("tr",
										new XElement("th", "Type"),
										new XElement("th", "Count"),
										new XElement("th", "Total Size")
									)
								),
								new XElement("tbody",
									// LINQ query
									from file in files
									group file by Path.GetExtension(file).ToLower() into fileTypeGroup
									let totalGroupSize = fileTypeGroup.Sum(file => new FileInfo(file).Length)
									orderby totalGroupSize descending
									select new XElement("tr",
										// File type
										new XElement("td", fileTypeGroup.Key),
										// Total # of file type
										new XElement("td", fileTypeGroup.Count(),
											new XAttribute("align", "right")
										),
										// Total size of file type
										new XElement("td", FormatByteSize(totalGroupSize),
											new XAttribute("align", "right")
										)
									)
								)
							)
						)
					)
				);
			   
		
		public static void Main(string[] args)
		{
			// Version for CLI args
			/*
			try
			{
				string inputFolderPath = args[0], outputFilePath = args[1];
				CreateReport(EnumerateFilesRecursively(inputFolderPath)).Save(outputFilePath + "\\report.html");
			}
			catch
			{
				Console.WriteLine("Please enter a folder path and output path (for resulting report.html file).");
				Console.WriteLine("Usage: Lab4 <folder path> <output path>");
			}	
			*/

			// Version for Console App
			try
			{
				string inputFolderPath, outputFilePath;
				Console.WriteLine("Enter a folder path");
				inputFolderPath = Console.ReadLine();

				Console.WriteLine("Enter a path for the resulting report.html:");
				outputFilePath = Console.ReadLine();

				CreateReport(EnumerateFilesRecursively(inputFolderPath)).Save(outputFilePath + "\\report.html");
			}
			catch (Exception e)
			{
				Console.WriteLine("\nERROR:\n" + e.Message);
				Console.WriteLine("\nPlease enter a folder path and output path (for resulting report.html file).");
				Console.WriteLine("Usage:");
				Console.WriteLine("Enter a folder path");
				Console.WriteLine("C:\\your\\path\\here");
				Console.WriteLine("Enter a path for the resulting report.html:");
				Console.WriteLine("C:\\your\\path\\here");
			}
		}
	}
}
