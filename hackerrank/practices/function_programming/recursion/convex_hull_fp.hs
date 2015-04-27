import Text.Printf
import Data.List

{--

data Line = Line {
  a :: Double,
  b :: Double,
  c :: Double
  }

lineFromTwoPoint (x1, y1) (x2, y2) =
  Line {a = y1-y2, b = x2-x1, c = (y2-y1)*x1-(x2-x1)*y1}

pointDistFromLine (x, y) (Line a b c) =
  abs (a*x + b*y + c) / sqrt (a*a + b*b)

maximiumPoint ps (Line a b c) (x, y)
  | ps == [] = (x, y)
  | otherwise = if pointDistFromLine (x', y') (Line a b c) > pointDistFromLine (x, y) (Line a b c)
                then maximiumPoint rx (Line a b c) (x', y')
                else maximiumPoint rx (Line a b c) (x,  y)
                  where ((x', y'):rx) = ps

dist (x1, y1) (x2, y2) = sqrt ((x1-x2)**2 + (y1-y2)**2)

leftPoint [] (x, y) = (x, y)
leftPoint ((x', y'):ps) (x, y) = leftPoint ps (if x' < x then (x', y') else (x, y))

rightPoint [] (x, y) = (x, y)
rightPoint ((x', y'):ps) (x, y) = rightPoint ps (if x' > x then (x', y') else (x, y))

quickHull [] (x1, y1) (x2, y2) = []
quickHull ps (x1, y1) (x2, y2) =
  let (sx, sy) = maximiumPoint ps (lineFromTwoPoint (x1, y1) (x2, y2)) (x1, y1)
      Line a b c = lineFromTwoPoint (x1, y1) (sx, sy)
      ps1 = quickHull (filter (\(x, y) -> a*x + b*y + c > 0) ps) (x1, y1) (sx, sy)
      Line a' b' c' = lineFromTwoPoint (x2, y2) (sx, sy)
      ps2 = quickHull (filter (\(x, y) -> a'*x + b'*y + c' > 0) ps) (x1, y1) (sx, sy)
  in concat [ps1, ps2, [(sx, sy)]]

--}

leftBellowPoint ps (x, y)
  | ps == [] = (x, y)
  | otherwise = leftBellowPoint rs ( if (or [x' < x, and [x' == x, y' < y]]) then (x', y') else (x, y) )
    where (x', y'):rs = ps

cross (x1, y1) (x2, y2) = x1*y2 - y1*x2

convexHull :: [(Int, Int)] -> [(Int, Int)] -> [(Int, Int)]
convexHull points [] = convexHull (drop 1 points) (take 1 points)
convexHull [] stack = stack
convexHull points (x:[]) = convexHull (drop 1 points) [head points, x]
convexHull p@((x, y):ps) stack@((x1, y1):(x2, y2):ss) =
  if cross (x-x1, y-y1) (x2-x1, y2-y1) >= 0
  then convexHull ps ((x, y):stack)
  else convexHull p ((x2, y2):ss)

dist :: (Int, Int) -> (Int, Int) -> Double
dist (x1, y1) (x2, y2) =
  sqrt $ ( fromIntegral x1 - fromIntegral x2 )**2 + ( fromIntegral y1 - fromIntegral y2 )**2

-- solve :: [(Int, Int)] -> Double
solve points =
  let lb@(lbx, lby) = leftBellowPoint points $ points !! 0
      ps = sortBy (\(x1,y1) (x2, y2) ->
        if ( or [cross (x1-lbx, y1-lby) (x2-lbx, y2-lby) > 0,
                  and [cross (x1-lbx, y1-lby) (x2-lbx, y2-lby) == 0,
                       (x1-lbx)*(x1-lbx)+(y1-lby)*(y1-lby) < (x2-lbx)*(x2-lbx)+(y2-lby)*(y2-lby)] ] )
        then LT
        else GT) points

      ans = convexHull ps []

  in foldr (\(x1, y1) ((x2, y2), ac) -> ( (x1, y1), ac+dist (x1, y1) (x2, y2) ) ) (head ans, 0) (ans ++ take 1 ans)

main = do
  n <- readLn :: IO Int
  content <- getContents
  let points = map (\[x, y] -> (x, y)). map (map (read::String->Int)). map words. lines $ content
      -- ans = solve points
  printf "%.1f\n" . snd. solve $ points
  -- printf "%.1f\n" ans

