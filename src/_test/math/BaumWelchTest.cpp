#include <gtest/gtest.h>
#include <gtest/gtest-message.h>
#include <gtest/internal/gtest-internal.h>
#include "../../config.h"
#include "../../math/BaumWelch.h"
#include "../model/HmmHelper.h"
#include <vector>

using namespace yazz;
using namespace yazz::model;
using namespace yazz::math;
using namespace std;

const double HMM_TEST_EPSILON = 1e-2;

static void checkModel(HmModel* model, double** transitionsX, double** emissionsX,
		double* initialDstX);

/**
 * The simplest test
 */
TEST(BAUM_WELCH, SIMPLE) {
	string text = "test";

	size_t stateCnt = 2;
	state_t* states = new state_t[2] {'s', 't'};

	size_t observationCnt = 2;
	observation_t* observations = new observation_t[2] {'A', 'B'};

	double** transitions = new double*[2] {
		new double[2] {0.3, 0.7},
		new double[2] {0.1, 0.9}
	};
	double** emissions = new double*[2] {
		new double[2] {0.4, 0.6},
		new double[2] {0.5, 0.5}
	};
	double* initialDst = new double[2] {0.85, 0.15};

	HmModel* model = new HmModel();
	model->init(states, stateCnt, observations, observationCnt,
			transitions, emissions, initialDst, text);

	vector<observation_t> sequence;
	sequence.push_back('A');
	sequence.push_back('B');
	sequence.push_back('B');
	sequence.push_back('A');

	// Model's attributes to check with
	double** transitionsX = new double*[2] {
		new double[2] {0.0, 1.0},
		new double[2] {0.47, 0.53}
	};
	double** emissionsX = new double*[2] {
		new double[2] {1.0, 0.0},
		new double[2] {0.02, 0.97}
	};
	double* initialDstX = new double[2] {1.0, 0.0};

	// Run the algorithm
	const vector<observation_t>* observationsConst = &sequence;
	BaumWelch::perform(model, observationsConst);

	// Check the results
	checkModel(model, transitionsX, emissionsX, initialDstX);
}

static void checkModel(HmModel* model, double** transitionsX, double** emissionsX,
		double* initialDstX) {
	for (size_t i = 0; i < model->getStateCnt(); i++) {
		for (size_t j = 0; j < model->getStateCnt(); j++) {
			EXPECT_NEAR(model->getTransitions()[i][j], transitionsX[i][j], HMM_TEST_EPSILON);
		}
	}

	for (size_t i = 0; i < model->getStateCnt(); i++) {
		for (size_t j = 0; j < model->getObservationCnt(); j++) {
			EXPECT_NEAR(model->getEmissions()[i][j], emissionsX[i][j], HMM_TEST_EPSILON);
		}
	}

	for (size_t i = 0; i < model->getStateCnt(); i++) {
		EXPECT_NEAR(model->getInitialDst()[i], initialDstX[i], HMM_TEST_EPSILON);
	}
}
