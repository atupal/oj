{-
The Fibonacci sequence is defined by the recurrence relation:
Hence the first 12 terms will be:
The 12th term, F
, is the first term to contain three digits.
What is the first term in the Fibonacci sequence to contain 1000 digits?
-}

fib (ind, x,y) = (ind, x, y):fib(ind+1, y, x+y)

main = print ( head [ ind | (ind, val, _) <- fib (1,1,1), val >= (10^999) ] )
