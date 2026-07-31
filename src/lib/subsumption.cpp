#include "subsumption.hpp"
#include "cnf.hpp"
#include "unification.hpp"

namespace
{
static bool subsumesHelper(const std::vector<Literal> &aLits, std::size_t idx,
                           const std::vector<Literal> &cLits, std::vector<bool> &used,
                           Substitution sigma)
{
    if (idx == aLits.size())
        return true;
    const Literal &aLit = aLits[idx];
    for (std::size_t j = 0; j < static_cast<std::size_t>(cLits.size()); j++)
    {
        if (used[j] || cLits[j].positive != aLit.positive)
            continue;
        for (int swap = 0; swap < 2; swap++)
        {
            const Term &pl = swap ? aLit.right : aLit.left;
            const Term &pr = swap ? aLit.left : aLit.right;
            auto s = matchTerm(pl, cLits[j].left, sigma);
            if (!s)
                continue;
            s = matchTerm(pr, cLits[j].right, *s);
            if (!s)
                continue;
            used[j] = true;
            if (subsumesHelper(aLits, idx + 1, cLits, used, *s))
                return true;
            used[j] = false;
        }
    }
    return false;
}

} // namespace

SubsumptionIndex::SubsumptionIndex(bool useFeatureVectorIndex)
{
    if (useFeatureVectorIndex)
        impl_ = FeatureVectorIndex<std::size_t>{};
    else
        impl_ = LinearIndex<Clause, std::size_t>{};
}

void SubsumptionIndex::insert(const Clause &c, std::size_t entry)
{
    std::visit([&](auto &idx) { idx.insert(c, entry); }, impl_);
}

std::vector<std::size_t> SubsumptionIndex::candidates(const Clause &c) const
{
    return std::visit([&](const auto &idx) { return idx.candidates(c); }, impl_);
}

bool subsumes(const Clause &A, const std::vector<Literal> &cLits)
{
    if (A.literals.size() > cLits.size())
        return false;
    std::vector<Literal> aLits(A.literals.begin(), A.literals.end());
    std::vector<bool> used(cLits.size(), false);
    return subsumesHelper(aLits, 0, cLits, used, {});
}

bool subsumes(const Clause &A, const Clause &C)
{
    std::vector<Literal> cLits(C.literals.begin(), C.literals.end());
    return subsumes(A, cLits);
}
