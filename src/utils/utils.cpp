#include "utils/utils.h"

const char *modeToString(Mode mode)
{
    switch (mode)
    {
    case NIR_LIGHT:
        return "PLACEBO";
    case PLACEBO:
        return "NOT_PLACEBO";
    case RANDOMIZED:
        return "DOUBLE_BLINDED";
    default:
        return "UNKNOWN_MODE";
    }
}

const char *durationToString(Duration duration)
{
    switch (duration)
    {
    case DURATION_20_MIN:
        return "DURATION_20_MIN";
    case DURATION_30_MIN:
        return "DURATION_35_MIN";
    case DURATION_40_MIN:
        return "DURATION_40_MIN";
    default:
        return "UNKNOWN_DURATION";
    }
}

const char *pvmFreqToString(PvmFreq pvmFreq)
{
    switch (pvmFreq)
    {
    case CONTINOUS:
        return "CONTINUOUS";
    case LOW_FREQ:
        return "LOW_FREQUENCY";
    case HIGH_FREQ:
        return "HIGH_FREQUENCY";
    default:
        return "UNKNOWN_PVM_FREQ";
    }
}