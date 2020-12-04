#ifndef RUNS_h
#define RUNS_h

#include "MotorDriver.h"

#define FILTER_COLOR_NONE     0
#define FILTER_COLOR_GREY     1
#define FILTER_COLOR_BLUE     2
#define FILTER_COLOR_GREEN    3
#define FILTER_COLOR_ORANGE   4
#define FILTER_COLOR_RED      5

#define POS_LEFT              0
#define POS_RIGHT             1
#define POS_MIDDLE            3

int32_t s32RunsMotorStop(void);
void vRunsSerialMode();
void vRunsInitRun(uint32_t initPosition);
void vRunsMoveTo(int32_t positionAbsolute);
void vProcessSlitsRun(uint8_t sampleRun, uint8_t step);
void vProcessWLRun(uint8_t sampleRun, uint8_t step);
void vRunsTestMoveTo();
void vRunsExampleRun(uint8_t run);
void vRunsStepLoseCheck();
void vRunsMoveToSpecialPos(uint8_t u8pos);
int32_t vRunsMoveToLsSig(int32_t targetPosition, int32_t* decSteps);
void vRunsOffsetInFrontLsRun(uint32_t* steps);
void vRunsOffsetBehindLsRun(uint32_t* steps);
void vRunsStartOffsetRun();

void vRunsMoveToWl(uint16_t u16wl, uint8_t monochromatorType);
void vRunsMoveGratingToWl(uint16_t u16wl, uint8_t monochromatorType);
void vRunsMoveFilterToWl(uint16_t u16wl, uint8_t monochromatorType);
void vRunsMoveToSlitPos(uint8_t u8slitAxis, float fSlitWidth);
#endif
