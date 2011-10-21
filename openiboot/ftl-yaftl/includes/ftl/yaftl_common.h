#ifndef FTL_YAFTL_COMMON_H
#define FTL_YAFTL_COMMON_H

#include "openiboot.h"
#include "util.h"
#include "ftl/yaftl_mem.h"

/* Macros */

// YAFTL errors
#define ERROR_ARG	0x80000001
#define ERROR_NAND	0x80000002
#define ERROR_EMPTY	0x80000003

// Page types (as defined in the spare data "type" bitfield)
#define PAGETYPE_INDEX		(0x4)	// Index block indicator
#define PAGETYPE_CLOSED		(0x8)	// Closed (full) block
#define PAGETYPE_LBN		(0x10)	// User data (also called lbn: maybe logical block number? lBlock 0 is system and lBlock 1 is user?)
#define PAGETYPE_FTL_CLEAN	(0x20)	// FTL context (unmounted, clean)
// 0x40: ?
#define PAGETYPE_VFL		(0x80)	// VFL context

// Block status (as defined in the BlockStruct structure)
#define BLOCKSTATUS_ALLOCATED		(0x1)
#define BLOCKSTATUS_FTLCTRL			(0x2)
#define BLOCKSTATUS_GC				(0x4)
#define BLOCKSTATUS_CURRENT			(0x8)
#define BLOCKSTATUS_FTLCTRL_SEL		(0x10)
#define BLOCKSTATUS_I_GC			(0x20)
#define BLOCKSTATUS_I_ALLOCATED		(0x40)
#define BLOCKSTATUS_I_CURRENT		(0x80)
#define BLOCKSTATUS_FREE			(0xFF)

// Cache states
#define CACHESTATE_DIRTY	(0x1)
#define CACHESTATE_CLEAN	(0x2)
#define CACHESTATE_FREE		(0xFFFF)

// Size of GCList
#define GCLIST_MAX (16)

/* Types */

typedef struct {
	uint32_t lpn;			// Logical page number
	uint32_t usn;			// Update sequence number
	uint8_t  field_8;
	uint8_t  type;			// Page type
	uint16_t field_A;
} __attribute__((packed)) SpareData;

typedef struct {
	uint32_t eraseCount;
	uint16_t validPagesDNo;			// Data validity counter
	uint16_t validPagesINo;			// Index validity counter
	uint16_t readCount;				// Number of reads
	uint8_t status;					// Block status
	uint8_t unkn5;
} BlockStruct;

typedef struct {
	uint32_t indexPage;
	uint16_t cacheNum;
	uint16_t TOCUnkMember2;
} __attribute__((packed)) TOCStruct;

typedef struct {
	uint32_t* buffer;
	uint32_t page;
	uint16_t useCount;
	uint16_t state;
} __attribute__((packed)) TOCCache;

typedef struct {
	uint32_t numAllocated; // 00
	uint32_t numAvailable; // 04
	uint32_t numValidDPages; // 08
	uint32_t numIAllocated; // 0C
	uint32_t numIAvailable; // 10
	uint32_t numValidIPages; // 14
	uint32_t numFree; // 18
	uint32_t field_1C; // 1C
} __attribute__((packed)) BlockStats;

typedef struct {
	uint32_t blockNum;
	uint32_t* tocBuffer;
	uint32_t usedPages;
	uint16_t field_A;
	uint32_t usn;
} BlockToUse;

typedef struct _L2VNode {
	struct _L2VNode* next;
} L2VNode;

typedef struct {
	uint32_t block[GCLIST_MAX + 1];
	uint32_t head;
	uint32_t tail;
} GCList;

typedef struct {
	uint32_t pageIndex;
	uint32_t field_4;
	uint32_t vpn;
	uint32_t span;
	L2VNode* node;
	uint32_t field_14;
	uint32_t next_nOfs;
	uint32_t nodeSize;
	uint32_t field_20;
	uint32_t field_24;
} GCReadC;

typedef struct {
	uint32_t victim;
	GCList list;
	uint32_t chosenBlock;
	uint32_t totalValidPages;
	uint32_t eraseCount;
	uint32_t* btoc;
	uint8_t* pageBuffer1;
	uint32_t* zone;
	uint8_t* pageBuffer2;
	SpareData* spareArray;
	uint32_t curZoneSize;
	uint32_t uECC;
	uint32_t state;
	uint32_t btocIdx;
	uint32_t dataPagesPerSublk;
	uint32_t numInvalidatedPages;
	GCReadC read_c;
} GCData;

typedef struct {
	GCData data;
	GCData index;
} GC;

typedef struct {
	bufzone_t zone;
	bufzone_t segment_info_temp;
	uint16_t tocPagesPerBlock; // 38
	uint16_t tocEntriesPerPage; // 3A
	uint32_t numIBlocks; // 3C
	uint32_t unknCalculatedValue1; // 40
	uint32_t totalPages; // 44
	uint16_t tocArrayLength; // 48
	uint16_t numFreeCaches; // 4A
	uint32_t ftlCxtUsn;
	uint32_t field_64;
	uint32_t selCtrlBlockIndex;
	uint8_t totalEraseCount;
	BlockToUse latestUserBlk;
	BlockToUse latestIndexBlk;
	uint32_t maxIndexUsn; // 6C
	uint32_t field_A4;
	uint8_t field_78; // Heh, wtf?
	uint32_t unk74_4;
	uint32_t unk78_counter;
	uint32_t unk7C_byteMask;
	uint32_t unk80_3;
	uint32_t** unk84_buffer;
	uint32_t* unk88_buffer;
	uint32_t* unk8c_buffer;
	bufzone_t ftl_buffer2;
	uint32_t unkAC_2;
	uint32_t unkB0_1;
	uint32_t* unkB4_buffer;
	uint8_t** unkB8_buffer;
	BlockStats blockStats; // BC
	uint32_t field_DC[4]; // DC
	TOCStruct* tocArray; // EC
	TOCCache* tocCaches; // F0
	BlockStruct* blockArray; // F4
	uint32_t* pageBuffer2;
	SpareData* spareBuffer3;
	SpareData* spareBuffer4;
	SpareData* spareBuffer5;
	SpareData* spareBuffer6;
	SpareData* spareBuffer7;
	SpareData* spareBuffer8;
	SpareData* spareBuffer9;
	SpareData* spareBuffer10;
	SpareData* spareBuffer11;
	SpareData* spareBuffer12;
	SpareData* spareBuffer13;
	SpareData* spareBuffer14;
	SpareData* spareBuffer15;
	SpareData* spareBuffer16;
	SpareData* spareBuffer17;
	uint8_t* pageBuffer;
	uint32_t* tocPageBuffer;
	uint32_t lastTOCPageRead;
	SpareData* spareBuffer19;
	uint32_t* unknBuffer3_ftl; // 148
	SpareData* buffer20;
	SpareData* spareBuffer18;
	uint32_t ctrlBlockPageOffset;
	uint32_t nPagesTocPageIndices;
	uint32_t nPagesBlockStatuses;
	uint32_t nPagesBlockReadCounts;
	uint32_t nPagesBlockEraseCounts;
	uint32_t nPagesBlockValidPagesDNumbers;
	uint32_t nPagesBlockValidPagesINumbers;
	uint32_t ftlCxtPage;
	uint16_t FTLCtrlBlock[3];
	uint16_t unkn_1;
	uint32_t maxBlockEraseCount;
	uint32_t minBlockEraseCount;
	uint32_t numCaches;
	uint8_t unk188_0x63;
	uint32_t pagesAvailable;
	uint32_t bytesPerPage;
	uint32_t gcPages;
	GC gc;
	bufzone_t gcBufZone;
	SpareData* gcSpareBuffer;
	GCReadC readc;
} YAFTLInfo;

typedef struct {
	uint16_t pagesPerSublk;
	uint16_t numBlocks;
	uint16_t bytesPerPage;
	uint16_t spareDataSize;
	uint16_t total_banks_ftl;
	uint32_t total_usable_pages;
} NAND_GEOMETRY_FTL;

typedef struct {
	char version[4]; // 0
	uint32_t numIBlocks; // 4
	uint32_t totalPages; // 8
	uint32_t latestUserBlk; // C
	uint32_t cxt_unkn0; // 10 // placeholder
	uint32_t latestIndexBlk; // 14
	uint32_t maxIndexUsn; // 18
	uint32_t numAvailableBlocks; // 1C
	uint32_t numIAvailableBlocks; // 20
	uint32_t numAllocatedBlocks; // 24
	uint32_t numIAllocatedBlocks; // 28
	uint32_t numCaches; // 2C
	uint32_t cxt_unkn1[10]; // placeholder
	uint32_t field_58; // 58
	uint16_t tocArrayLength; // 5C
	uint16_t tocPagesPerBlock; // 5E
	uint16_t tocEntriesPerPage; // 60
	uint16_t numFreeCaches; // 62
	uint16_t pagesUsedInLatestUserBlk; // 66
	uint16_t pagesUsedInLatestIdxBlk; // 68
	uint32_t cxt_unkn2[11]; // placeholder
	uint8_t unk188_0x63; // 94
} __attribute__((packed)) YAFTL_CXT;

typedef struct _BlockListNode {
	uint32_t usn;
	uint16_t blockNumber;
	uint16_t field_6;
	struct _BlockListNode *next;
	struct _BlockListNode *prev;
} __attribute__((packed)) BlockListNode;

typedef struct {
	uint32_t lpnMin;
	uint32_t lpnMax;
} __attribute__((packed)) BlockLpn;

/* Externs */

extern YAFTLInfo sInfo;
extern NAND_GEOMETRY_FTL sGeometry;
extern uint32_t yaftl_inited;
extern vfl_device_t* vfl;

/* Functions */

void YAFTL_allocateNewBlock(uint8_t isUserBlock);

error_t YAFTL_closeLatestBlock(uint8_t isUserBlock);

uint32_t* YAFTL_allocBTOC(uint32_t _arg0);

error_t YAFTL_readPage(uint32_t _page, uint8_t* _data_ptr, SpareData* _spare_ptr, uint32_t _disable_aes, uint32_t _empty_ok, uint32_t _scrub);

uint32_t YAFTL_writePage(uint32_t _page, uint8_t* _data_ptr, SpareData* _spare_ptr);

error_t YAFTL_writeIndexTOC();

uint32_t YAFTL_findFreeTOCCache();

uint32_t YAFTL_clearEntryInCache(uint16_t _cacheIdx);

void YAFTL_copyBTOC(uint32_t* dest, uint32_t* src, uint32_t maxVal);

#endif // FTL_YAFTL_COMMON_H
