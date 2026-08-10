#include "testlib.h"

#include <algorithm>
#include <climits>
#include <cmath>
#include <queue>
#include <vector>

using namespace std;

namespace {

long double score_ratio(long long maximum_stack_id) {
    if (maximum_stack_id <= 180) {
        return 1.0L;
    }
    if (maximum_stack_id <= 280) {
        return (1540.0L - 3.0L * maximum_stack_id) / 1000.0L;
    }
    if (maximum_stack_id <= 1000) {
        return (1540.0L - maximum_stack_id) / 1800.0L;
    }
    if (maximum_stack_id <= 1000000) {
        return 3.0L / cbrt(static_cast<long double>(maximum_stack_id));
    }
    return 0.0L;
}

}  // namespace

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    const int n = inf.readInt(1, 500000, "n");
    const int card_count = 2 * n;

    vector<int> rank(card_count);
    vector<int> frequency(n + 1, 0);
    for (int i = 0; i < card_count; ++i) {
        rank[i] = inf.readInt(1, n, "card rank");
        ++frequency[rank[i]];
    }
    if (!inf.seekEof()) {
        quitf(_fail, "invalid judge input: extra tokens after the deck");
    }

    for (int value = 1; value <= n; ++value) {
        if (frequency[value] != 2) {
            quitf(
                _fail,
                "invalid judge input: rank %d occurs %d times",
                value,
                frequency[value]
            );
        }
    }

    vector<long long> stack_id(card_count);
    long long maximum_stack_id = 0;
    for (int i = 0; i < card_count; ++i) {
        stack_id[i] = ouf.readLong(1LL, LLONG_MAX, "stack id");
        maximum_stack_id = max(maximum_stack_id, stack_id[i]);
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after the required %d stack ids", card_count);
    }

    // Compress only for legality checking. Scoring uses maximum_stack_id above.
    vector<long long> compressed_ids = stack_id;
    sort(compressed_ids.begin(), compressed_ids.end());
    compressed_ids.erase(
        unique(compressed_ids.begin(), compressed_ids.end()),
        compressed_ids.end()
    );

    const int stack_count = static_cast<int>(compressed_ids.size());
    vector<int> top_card(stack_count, -1);
    vector<int> previous_card(card_count, -1);
    vector<int> first_stack(n + 1, -1);
    vector<int> second_stack(n + 1, -1);

    for (int i = 0; i < card_count; ++i) {
        const int stack = static_cast<int>(
            lower_bound(
                compressed_ids.begin(),
                compressed_ids.end(),
                stack_id[i]
            ) - compressed_ids.begin()
        );

        previous_card[i] = top_card[stack];
        top_card[stack] = i;

        const int value = rank[i];
        if (first_stack[value] == -1) {
            first_stack[value] = stack;
        } else {
            second_stack[value] = stack;
            if (first_stack[value] == second_stack[value]) {
                quitf(
                    _wa,
                    "rank %d has both cards in the same stack",
                    value
                );
            }
        }
    }

    // Simulate all currently possible eliminations. If two equal ranks are
    // simultaneously exposed, eliminating them cannot invalidate another
    // available pair because one stack has only one top card.
    vector<unsigned char> exposed_count(n + 1, 0);
    queue<int> ready;

    for (int stack = 0; stack < stack_count; ++stack) {
        const int card = top_card[stack];
        if (card == -1) {
            continue;
        }
        const int value = rank[card];
        ++exposed_count[value];
        if (exposed_count[value] == 2) {
            ready.push(value);
        }
    }

    int removed_cards = 0;
    while (!ready.empty()) {
        const int value = ready.front();
        ready.pop();

        const int left_stack = first_stack[value];
        const int right_stack = second_stack[value];
        const int left_card = top_card[left_stack];
        const int right_card = top_card[right_stack];

        if (
            left_card == -1 ||
            right_card == -1 ||
            rank[left_card] != value ||
            rank[right_card] != value
        ) {
            quitf(_fail, "checker invariant failed while removing rank %d", value);
        }

        top_card[left_stack] = previous_card[left_card];
        top_card[right_stack] = previous_card[right_card];
        removed_cards += 2;

        const int changed_stacks[2] = {left_stack, right_stack};
        for (int index = 0; index < 2; ++index) {
            const int stack = changed_stacks[index];
            const int card = top_card[stack];
            if (card == -1) {
                continue;
            }
            const int newly_exposed_rank = rank[card];
            ++exposed_count[newly_exposed_rank];
            if (exposed_count[newly_exposed_rank] == 2) {
                ready.push(newly_exposed_rank);
            }
        }
    }

    if (removed_cards != card_count) {
        quitf(
            _wa,
            "construction is not eliminable: removed %d of %d cards",
            removed_cards,
            card_count
        );
    }

    long double ratio = score_ratio(maximum_stack_id);
    ratio = max(0.0L, min(1.0L, ratio));
    const double percentage = static_cast<double>(100.0L * ratio);

    if (ratio >= 1.0L) {
        quitf(
            _ok,
            "valid construction: max stack id = %lld, score = 100%%",
            maximum_stack_id
        );
    }

    quitp(
        static_cast<double>(ratio*100),
        "valid construction: max stack id = %lld, score = %.6f%%",
        maximum_stack_id,
        percentage
    );
}
