
module Main where

c :: Int -> Int -> Int
c _ 0 = 1
c n m
  | m > n = 0
  | n == m = 1
  | otherwise = c (n-1) m + c (n-1) (m-1)

pline n ind = do
  if ind < 0 then
             putStrLn ""
             else
             do
               putStr . show . c n $ ind
               putStr " "
               pline n (ind-1)


main = do
  input <- getLine
  let n = (read :: String -> Int) input
  mapM_ (\x -> pline x x) [0..n-1]
