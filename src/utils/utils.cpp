#include "utils/utils.h"

const char *modeToString(Mode mode)
{
    switch (mode)
    {
    case NIR_LIGHT:
        return "NIR-lys";
    case PLACEBO:
        return "Placebo";
    case RANDOMIZED:
        return "Randomisert";
    default:
        return "UNKNOWN_MODE";
    }
}

const char *durationToString(Duration duration)
{
    switch (duration)
    {
    case DURATION_20_MIN:
        return "20 min";
    case DURATION_30_MIN:
        return "30 min";
    case DURATION_40_MIN:
        return "40 min";
    default:
        return "UNKNOWN_DURATION";
    }
}

const char *pvmFreqToString(PvmFreq pvmFreq)
{
    switch (pvmFreq)
    {
    case CONTINOUS:
        return "Kontinuerlig";
    case LOW_FREQ:
        return "Lav frekvent";
    case HIGH_FREQ:
        return "Hoy frekvent";
    default:
        return "UNKNOWN_PVM_FREQ";
    }
}