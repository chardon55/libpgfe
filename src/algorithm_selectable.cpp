#include "algorithm_selectable.hpp"

using namespace chardon55::PGFE;

void AlgorithmSelectable::select_algorithm(pgfe_algorithm_choice choice) {
    if (choice == cur_alg) return;

    before_change_alg();
    cur_alg = choice;
    after_change_alg();
}

pgfe_algorithm_choice AlgorithmSelectable::algorithm() const {
    return cur_alg;
}