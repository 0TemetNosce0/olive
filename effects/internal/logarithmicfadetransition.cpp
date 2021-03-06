#include "logarithmicfadetransition.h"

#include <QtMath>

LogarithmicFadeTransition::LogarithmicFadeTransition(Clip* c, const EffectMeta* em) : Effect(c, em) {}

void LogarithmicFadeTransition::process_audio(double timecode_start, double timecode_end, quint8* samples, int nb_bytes, int type) {
	double interval = (timecode_end-timecode_start)/nb_bytes;

	for (int i=0;i<nb_bytes;i+=2) {
		qint16 samp = (qint16) (((samples[i+1] & 0xFF) << 8) | (samples[i] & 0xFF));

		switch (type) {
		case TRAN_TYPE_OPEN:
		case TRAN_TYPE_OPENWLINK:
			samp *= qSqrt(timecode_start + (interval * i));
			break;
		case TRAN_TYPE_CLOSE:
		case TRAN_TYPE_CLOSEWLINK:
			samp *= qSqrt(1 - (timecode_start + (interval * i)));
			break;
		}

		samples[i+1] = (quint8) (samp >> 8);
		samples[i] = (quint8) samp;
	}
}
