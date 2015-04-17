module Main where

cross (x1, y1) (x2, y2) = x1*y2 - x2*y1

isInTriangle (x, y) ( (ax, ay), (bx, by), (cx, cy) ) iter
  | iter == 0 = True
  | and [cx-bx==2, cx+bx==x*2, y==by] = False
  | y >= ( (ay+by+1)/2 ) = isInTriangle (x, y) ( (ax, ay), ( (ax+bx+1)/2, (ay+by+1)/2 ), ( (ax+cx-1)/2, (ay+cy+1)/2 ) ) (iter-1)
  | cross ((ax+bx-1)/2-x, (ay+by-1)/2-y) ((bx+cx-2)/2-x, (by+cy)/2-y) <= 0 = isInTriangle (x, y) ( ((ax+bx-1)/2, (ay+by-1)/2), (bx, by), ((bx+cx-2)/2, (by+cy)/2) )  (iter-1)
  | cross ((ax+cx+1)/2-x, (ay+cy-1)/2-y) ((bx+cx+2)/2-x, (by+cy)/2-y) >= 0 = isInTriangle (x, y) ( ((ax+cx+1)/2, (ay+cy-1)/2), ((bx+cx+2)/2, (by+cy)/2), (cx, cy) )  (iter-1)
  | otherwise = False

printAChar n iter x
  | x <= 32-n = putStr "_"
  | x >= 32+n = putStr "_"
  | otherwise = if isInTriangle (fromIntegral x, fromIntegral (-n)) ( (32, -1), (1, -32), (63, -32) ) iter
                then putStr "1"
                else putStr "_"

printLine n iter = do
  mapM_  (printAChar n iter) $ [1..63]
  putStrLn ""

main = do
  input <- getLine
  let n = (read :: String -> Int) input
  mapM_ (\x -> printLine x n) [1..32]
