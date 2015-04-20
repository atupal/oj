tree (x, y) hight iter
  | iter == 0 = []
  | otherwise = concat
                [concat [ [ (x, y') | y' <- [y..y+hight-1]],
                           zip [x-1,x-2..x-hight] [y+hight..y+hight*2-1],
                           zip [x+1..x+hight] [y+hight..y+hight*2-1]],
                concat [tree (x-hight, y+hight*2) (hight/2) (iter-1), tree (x+hight, y+hight*2) (hight/2) (iter-1)] ]

printLine t y = do
  mapM_ (\x -> if (x, y) `elem` t then putStr "1" else putStr "_") [1..100]
  putStrLn ""

printTree n = do
  let t = tree (50, 1) 16 n
  -- print t
  --mapM_ (\x -> if x `elem` t then putStr "1" else putStr "_")
    --[(x, y) | x <- [1..50], y <- [1..63]]
  mapM_ (printLine t) [63, 62..1]

main = do
  line <- getLine
  let n = (read :: String -> Int) line
  printTree n
