{-
A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:
012   021   102   120   201   210
What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
-}

{- import Data.List (permutations) -}

{- import Data.List (delete) -}
{- permutations :: Eq a => [a] -> [[a]]
- permutations [] = [[]]
- permutations xs = [ x:ys | x <- xs, ys <- permutations (delete x xs)] -}

permutations :: [a] -> [[a]]
permutations [] = [[]]
permutations xs = [ y:zs | (y,ys) <- select xs, zs <- permutations ys]
  where select []     = []
        select (x:xs) = (x,xs) : [ (y,x:ys) | (y,ys) <- select xs ]

{-
permutations :: [a] -> [[a]]
permutations = foldr (concatMap . insertEverywhere) [[]]
  where insertEverywhere :: a -> [a] -> [[a]]
        insertEverywhere x [] = [[x]]
        insertEverywhere x l@(y:ys) = (x:l) : map (y:) (insertEverywhere x ys)
-}

main = putStrLn (head (drop 999999 (permutations ['0'..'9'])) ) 
