

main = do
  p <- getLine
  q <- getLine
  mapM_ (\(a, b) -> do putStr [a, b]) $ zip p q
