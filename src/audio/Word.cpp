#include <Word.h>
#include <cstdint>
#include <string>

namespace yazz {
namespace audio {

Word::Word(uint32_t id) {
	this->id = id;

	this->mfccSize = 0;
	this->mfcc = 0;
}

Word::~Word() {
	if (NULL != mfcc) {
		delete [] mfcc;
	}
}

} /* namespace audio */
} /* namespace yazz */
