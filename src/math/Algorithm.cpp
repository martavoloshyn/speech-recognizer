#include "../config.h"
#include <assert.h>
#include <Algorithm.h>

namespace yazz {
namespace math {

const int INVALID_INDEX = -1;

void Algorithm::initObservationsMap(map<observation_t, uint32_t>& observMap,
		const vector<observation_t>* data,
		observation_t* observations, size_t observationsCnt) {

	for (vector<observation_t>::const_iterator iter = data->begin();
			iter != data->end(); iter++) {

		observation_t value = *iter;
		int32_t index = -INVALID_INDEX;

		for (uint32_t i = 0; i < observationsCnt; i++) {
			if (value == observations[i]) {
				index = i;
				break;
			}
		}

		assert("Unknown observation" && INVALID_INDEX != index);

		observMap[value] = index;
	}

	if (DEBUG_ENABLED) {
		cout << "Observation map is: ";
		for (map<observation_t, uint32_t>::iterator iter = observMap.begin(); iter != observMap.end(); ++iter) {
			cout << (*iter).first << "->" << (*iter).second << " ";
		}
		cout << endl << endl;
	}
}

double Algorithm::getObservProb(observation_t observation, size_t stateId,
		double** emissions, map<observation_t, uint32_t>& observMap) {
	double probability = 0.0;

	assert("Unknown observation" && INVALID_INDEX != observMap[observation]);

	int32_t index = observMap[observation];
	if (index >= 0) {
		probability = emissions[stateId][index];
	}

	return probability;
}

} /* namespace math */
} /* namespace yazz */
