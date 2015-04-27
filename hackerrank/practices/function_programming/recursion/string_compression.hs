
compress :: String -> Char -> Int -> String -> String
compress [] pre cnt ans = if cnt == 1 then (pre:ans) else (reverse . show $ cnt) ++ (pre:ans)
compress (x:ss) pre cnt ans
  | x/=pre = compress ss x 1 (if cnt==1 then (pre:ans) else (reverse . show $ cnt) ++ (pre:ans))
  | otherwise = compress ss pre (cnt+1) ans

main = do
  s <- getLine
  let (x:ss) = s
  putStrLn . reverse . (compress ss x 1) $ ""
