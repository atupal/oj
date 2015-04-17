
solve [] = []
solve (a:b:ss) = b:a:(solve ss)

permute = getLine >>= putStrLn . solve

main = do
  t <- readLn :: IO Int
  mapM_ (\_ -> permute) [1..t]
