//
// Created by Long Gong on 9/19/17.
//

#ifndef SABER_SAMPLE_HPP
#define SABER_SAMPLE_HPP

#include <vector>
#include <random>

namespace saber {
    /** @brief Vose's Algorithm Based Weighted Sampling With Replacement
     *
     * @tparam RandomAccessIterator
     * @tparam RandomNumberGenerator
     * @param m
     * @param first
     * @param last
     * @param gen
     * @return
     */
    template <class RandomAccessIterator, class RandomNumberGenerator>
    std::vector<size_t> sample(size_t m, RandomAccessIterator first, RandomAccessIterator last, RandomNumberGenerator& gen){
        typename std::iterator_traits<RandomAccessIterator>::difference_type n;
        n = (last - first);

        std::vector<size_t> larges(n, 0), smalls(n, 0), alias(n, 0);
        std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type> prob(n, 0);

        size_t j = 0, k = 0, l = 0, s = 0;
        const typename std::iterator_traits<RandomAccessIterator>::value_type avg = 1.0 / n;

        for (;j < n;++j) {
            if (first[j] > avg) larges[l ++] = j;
            else smalls[s ++] = j;
        }

        std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type> p(first, last);
        while (s != 0 && l != 0) {
            -- s; -- l;
            j = smalls[s];
            k = larges[l];
            prob[j] = n * p[j];
            alias[j] = k;

            p[k] += (p[j] - avg);

            if (p[k] > avg) larges[l ++ ] = k;
            else smalls[s ++] = k;
        }
        while (s > 0) prob[smalls[-- s]] = 1;
        while (l > 0) prob[larges[ -- l]] = 1;

        typename std::iterator_traits<RandomAccessIterator>::value_type u = 0;
        std::vector<size_t> samples(m, 0);

        for (auto& r: samples) {
            u = gen();
            j = static_cast<size_t>(u);
            if (u - j <= prob[j]) r = j;
            else r = alias[j];
        }

        return samples;
    }
    /**
     *
     * @tparam RandomAccessIterator
     * @param m
     * @param first
     * @param last
     * @return
     */
    template <class RandomAccessIterator>
    std::vector<size_t> sample(size_t m, RandomAccessIterator first, RandomAccessIterator last)
    {
        typename std::iterator_traits<RandomAccessIterator>::difference_type n;
        n = (last - first);

        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution(0.0, n);
        auto rng = std::bind(distribution, generator);

        return sample(m, first, last, rng);

    }
    /**
     *
     * @tparam RandomAccessIterator
     * @param first
     * @param last
     * @return
     */
    template <class RandomAccessIterator>
    typename std::iterator_traits<RandomAccessIterator>::value_type sample(RandomAccessIterator first, RandomAccessIterator last)
    {
        typename std::iterator_traits<RandomAccessIterator>::difference_type n;
        n = (last - first);

        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution(0.0, n);
        auto rng = std::bind(distribution, generator);

        return sample(1, first, last, rng)[0];
    }
    /**
     *
     * @tparam RandomAccessIterator
     * @tparam RandomNumberGenerator
     * @param first
     * @param last
     * @param gen
     * @return
     */
    template <class RandomAccessIterator, class RandomNumberGenerator>
    typename std::iterator_traits<RandomAccessIterator>::value_type sample(RandomAccessIterator first, RandomAccessIterator last, RandomNumberGenerator& gen) {
        return sample(1, first, last)[0];
    }
    /**
     *
     * @tparam RandomAccessIterator
     * @tparam UniformIntegerGenerator
     * @tparam UniformZeroOneRandomGenerator
     * @param m
     * @param first
     * @param last
     * @param u
     * @param gen
     * @return
     */
    template <class RandomAccessIterator, class UniformIntegerGenerator, class UniformZeroOneRandomGenerator>
    std::vector<size_t> roulette_wheel_selection(size_t m, RandomAccessIterator first, RandomAccessIterator last, UniformIntegerGenerator& u, UniformZeroOneRandomGenerator& gen){
        typename std::iterator_traits<RandomAccessIterator>::difference_type n;
        n = (last - first);

        std::vector<size_t> samples(m, 0);
        typename std::iterator_traits<RandomAccessIterator>::value_type w_max = *std::max_element(first, last);

        size_t j;
        for (auto& r: samples) {
            do {
                j = u();
            } while (gen() > first[j] / w_max);
            r = j;
        }

        return samples;
    }
    /**
     *
     * @tparam RandomAccessIterator
     * @param m
     * @param first
     * @param last
     * @return
     */
    template <class RandomAccessIterator>
    std::vector<size_t> roulette_wheel_selection(size_t m, RandomAccessIterator first, RandomAccessIterator last){
        typename std::iterator_traits<RandomAccessIterator>::difference_type n;
        n = (last - first);

        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        std::default_random_engine generator1;
        std::uniform_int_distribution<int> distribution1(0, n);

        auto rg = std::bind(distribution, generator);
        auto ug = std::bind(distribution1, generator1);

        return roulette_wheel_selection(m, first, last, ug, rg);
    }
    /**
     *
     * @tparam RandomAccessIterator
     * @param first
     * @param last
     * @return
     */
    template <class RandomAccessIterator>
    typename std::iterator_traits<RandomAccessIterator>::value_type roulette_wheel_selection(RandomAccessIterator first, RandomAccessIterator last){
        return roulette_wheel_selection(1, first, last)[0];
    }
    /**
     *
     * @tparam RandomAccessIterator
     * @tparam UniformIntegerGenerator
     * @tparam UniformZeroOneRandomGenerator
     * @param first
     * @param last
     * @param u
     * @param gen
     * @return
     */
    template <class RandomAccessIterator, class UniformIntegerGenerator, class UniformZeroOneRandomGenerator>
    typename std::iterator_traits<RandomAccessIterator>::value_type roulette_wheel_selection(RandomAccessIterator first, RandomAccessIterator last, UniformIntegerGenerator& u, UniformZeroOneRandomGenerator& gen){
        return roulette_wheel_selection(1, first, last, u, r)[0];
    }
};
#endif //SABER_SAMPLE_HPP
