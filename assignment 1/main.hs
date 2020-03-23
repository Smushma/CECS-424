module Main where

{-|
  Main 
-}
main = do 
  let list = [4, 65, 2, -31, 0, 99, 2, 83, 782, 1] --initialize test list
  putStrLn "Original list: " --prints line to console
  print(list) --prints list to console
  putStrLn "Quicksort:" --prints line to console
  print(qsort list) --prints result of 'qsort' function call with test parameter
  putStrLn "Mergesort:" --prints line to console
  print (msort list) --prints result of 'msort' function call with test parameter

{-|
  The 'qsort' function performs quicksort on a list
  It takes in one argument of type 'list' and returns a 'list'
  It contains an ordered datatype 
-}
qsort :: Ord a => [a] -> [a] 
qsort [] = [] --base case for recursion, if given an empty list to sort, the result is an empty list
--case for an appropriate list, x is the head and xs are the trailing elements
qsort (x : xs) = qsort sList ++ [x] ++ qsort lList --merges the lists so that the elements are in sorted order via recursion with 'x' as the pivot
  where --initialize variables
  sList = [small | small <- xs , small <= x] --list comprehension to put all  elements less than or equal to 'x' (pivot) into sList
  lList  = [large | large <- xs , large >  x] --list comprehension to put all elements greater than 'x' (pivot) into lList

{-|
  The 'split' function takes a list and splits it into two lists
  It takes in one argument of type 'list' and returns two 'lists'
  It cotains an ordered datatype
-}
split :: Ord a => [a] -> ([a], [a])
split [] = ([], []) --case for when splitting an empty list results in two empty lists
split [x] = ([x], []) --case for when splitting a non-empty list with 1 element results in itself and an empty list
split (x:y:zs) = let (xs, ys) = split zs in (x:xs, y:ys) --case for multiple elements in the parameter list, split the lists and recursively split each following list

{-|
  The function 'merge' takes two lists and merges it into one list
  It takes in two arguments of type 'list' and returns a 'list'
  It contains an ordered datatype
-}
merge :: Ord a => [a] -> [a] -> [a]
merge xs [] = xs --case for when combinining a non-empty list with an empty list results in the non-empty list
merge [] ys = ys --case for when combinining a non-empty list with an empty list results in the non-empty list
--case for two non-empty lists, compare the heads of each list
merge (x:xs) (y:ys) | x <= y = x : merge xs (y:ys) --if the first element in list 'x' is, set 'x' as the head of the "new" list and recursive 'merge' call on the remaining variables of each list
                    | otherwise = y : merge (x:xs) ys --set 'y' as the head of the "new" list and recursive 'merge' call on the remaining variables of each list

{-|
  The 'msort' function performs mergesort on a list
  It takes in one argument of type 'list' and returns a 'list'
  It contains an ordered datatype 
-}
msort :: Ord a => [a] -> [a]
msort [] = [] --base case for recursion, if given an empty list to sort, the result is an empty list
msort [a] = [a] --case for a list with a single element
msort xs = merge (msort ys) (msort zs) --call 'merge' function on the results of the recurisive 'msort' calls on each splitted half of the list
  where (ys, zs) = split xs --assign values to 'ys', 'zs' with the returned values of 'split xs'

