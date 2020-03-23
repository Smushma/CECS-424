module Main where

import Data.List
import Data.Ord

-- Person data type in "record syntax"
data Person = Person {name :: String, age :: Int} deriving (Show, Eq)

{-|
  Compares Person data type for sorting by name
-}
cmpPersonByName :: [Person] -> [Person]
cmpPersonByName = sortBy (comparing name)

{-|
  Compares Person data type for sorting by age
  If the ages are the same, order by name alphabetically
-}
cmpPersonByAge :: [Person] -> [Person]
cmpPersonByAge = sortBy $ flip $ (comparing age) -- For descending ages

{-|
  Main 
-}
main = do 
  print(sort[645.32, 37.40, 76.30, 5.40, -34.23, 1.11, -34.94, 23.37, 635.46, -876.22, 467.73, 62.26])
  putStrLn(" ")

  print(cmpPersonByName [Person "Hal" 20, Person "Susann" 31, Person "Dwight" 19, Person "Kassandra" 21, Person "Lawrence" 25, Person "Cindy" 22, Person "Cory" 27, Person "Mac" 19, Person "Romana" 27, Person "Doretha" 32, Person "Danna" 20, Person "Zara" 23, Person "Rosalyn" 26, Person "Risa" 24, Person "Benny" 28, Person "Juan" 33, Person "Natalie" 25])
  putStrLn(" ")

  print(cmpPersonByAge [Person "Hal" 20, Person "Susann" 31, Person "Dwight" 19, Person "Kassandra" 21, Person "Lawrence" 25, Person "Cindy" 22, Person "Cory" 27, Person "Mac" 19, Person "Romana" 27, Person "Doretha" 32, Person "Danna" 20, Person "Zara" 23, Person "Rosalyn" 26, Person "Risa" 24, Person "Benny" 28, Person "Juan" 33, Person "Natalie" 25])