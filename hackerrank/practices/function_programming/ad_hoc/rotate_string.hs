
rotate (s:ss) n
  | n == 0 = return ()
  | otherwise = do
    putStr (ss++[s])
    putStr " "
    rotate (ss++[s]) (n-1)

rotateString = do
  s <- getLine
  rotate s (length s)
  putStrLn ""

main = do
  s <- getLine
  let t = (read :: String -> Int) s
  mapM_ (\_ -> rotateString) [1..t]
