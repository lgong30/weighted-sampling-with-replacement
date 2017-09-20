# O(1) Weighted Sampling With Replacement

This repository implements two weighted sampling algorithms which run in amortized O(1) time per each sample. The first algorithm is based on [Vose's algorithm][1]. The other is based on [the roulette-wheel selection algorithm][2].


## Usage

see [tests](./tests)






[1]: Michael D. Vose. 1991. A Linear Algorithm for Generating Random Numbers with a Given Distribution. IEEE Trans. Softw. Eng. 17, 9 (September 1991), 972-975. DOI=http://dx.doi.org/10.1109/32.92917.  
[2]: Adam Lipowski, Dorota Lipowska, Roulette-wheel selection via stochastic acceptance, In Physica A: Statistical Mechanics and its Applications, Volume 391, Issue 6, 2012, Pages 2193-2196, ISSN 0378-4371, https://doi.org/10.1016/j.physa.2011.12.004.
     (http://www.sciencedirect.com/science/article/pii/S0378437111009010)