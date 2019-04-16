/*
* Copyright(c) 2019 Intel Corporation
* SPDX - License - Identifier: BSD - 2 - Clause - Patent
*/

#ifndef EbMotionEstimationLcuResults_h
#define EbMotionEstimationLcuResults_h

#include "EbDefinitions.h"
#include "EbDefinitions.h"
#ifdef __cplusplus
extern "C" {
#endif

#define MAX_ME_PU_COUNT         209  // Sum of all the possible partitions which have both deminsions greater than 4.

#define MAX_SS_ME_PU_COUNT       (849 * 4 + 5) // Sum of all the possible partitions which have both deminsions greater or equal to 4.

    // i.e. no 4x4, 8x4, or 4x8 partitions
#define SQUARE_PU_COUNT          85
#if MRP_ME
#define MAX_ME_CANDIDATE_PER_PU   24
#else
#define MAX_ME_CANDIDATE_PER_PU   3
#endif

    typedef struct MeCandidate_s {

        union {
            struct {
                signed short     xMvL0;  //Note: Do not change the order of these fields
                signed short     yMvL0;
                signed short     xMvL1;
                signed short     yMvL1;
            };
            uint64_t MVs;
        };

#if MRP_MEM_OPT
		unsigned    distortion : 32;     // 20-bits holds maximum SAD of 64x64 PU
		unsigned    direction : 2;
#if MRP_ME
		unsigned    ref_idx_l0 : 2;      // allows for up to 4 references   
		unsigned    ref_idx_l1 : 2;
#if MRP_MD_UNI_DIR_BIPRED 
		unsigned    ref0_list : 1;
		unsigned    ref1_list : 1;
#endif
#endif
#else

#if MRP_ME
        unsigned    ref_idx_l0 :  8;      // allows for up to 4 references   
        unsigned    ref_idx_l1 : 8;
#if MRP_MD_UNI_DIR_BIPRED 
        unsigned    ref0_list : 8;      
        unsigned    ref1_list : 8;
#endif
#endif
        unsigned    distortion : 32;     // 20-bits holds maximum SAD of 64x64 PU

        unsigned    direction : 8;      // 0: uni-pred L0, 1: uni-pred L1, 2: bi-pred
#endif
    } MeCandidate_t;

    // move this to a new file with ctor & dtor
    typedef struct MeLcuResults_s {

        uint32_t          lcuDistortion;
        uint8_t          *totalMeCandidateIndex;
        int16_t          xMvHmeSearchCenter[MAX_NUM_OF_REF_PIC_LIST][MAX_REF_IDX];
        int16_t          yMvHmeSearchCenter[MAX_NUM_OF_REF_PIC_LIST][MAX_REF_IDX];
        MeCandidate_t    **me_candidate;
        MeCandidate_t    *meCandidateArray;
#if MRP_ME
#if NSQ_OPTIMASATION
        uint8_t           *me_nsq_0; // 2 Number of reference lists
        uint8_t           *me_nsq_1; // 2 Number of reference lists
#endif
#endif

    } MeLcuResults_t;



#if !MRP_ME
    typedef struct  DistDir_s {
        unsigned    distortion : 32; //20bits are enough
        unsigned    direction : 2;
    } DistDir_t;


    typedef struct MeCuResults_s {
        union {
            struct {
                signed short     xMvL0;
                signed short     yMvL0;
                signed short     xMvL1;
                signed short     yMvL1;
            };
            uint64_t MVs;
        };

        DistDir_t    distortionDirection[3];

        uint8_t        totalMeCandidateIndex;
#if NSQ_OPTIMASATION
        uint8_t       me_nsq[2]; // 2 Number of reference lists
#endif
    } MeCuResults_t;
#endif
#ifdef __cplusplus
}
#endif
#endif // EbMotionEstimationLcuResults_h
