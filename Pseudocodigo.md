# Algo Docs
https://github.com/deroproject/astrobwt
AstroBWT Pseudo CODE v3
1. Calulate SHA3-256 of input data
2. Expand data using Salsa20  cipher  69371  bytes
3. Calculate BWT of step 2
4. Calculate SHA3-256 of BWT data
5. Expand data using Salsa20  cipher  69371  + random number based on step 4
6. Calculate BWT of data from step 5
7. Calculate SHA3-256 of BWT data from step 6

# Daemon RPC API Docs
https://github.com/deroproject/documentation
