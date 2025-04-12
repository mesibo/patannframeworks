#import <Foundation/Foundation.h>

#ifdef SO_BUILD
  #define SYMBOL_EXPORT __attribute__((visibility("default")))
#else
  #define SYMBOL_EXPORT
#endif

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(PatANNResults)
@interface PatANNResultsObjC : NSObject

@property (nonatomic, assign) int32_t count;
@property (nonatomic, assign) int32_t alloced;
@property (nonatomic, assign) int32_t mergeIndex;
@property (nonatomic, strong, nullable) NSArray<NSNumber *> *ids;  
@property (nonatomic, strong, nullable) NSArray<NSNumber *> *distances;

@end

NS_SWIFT_NAME(PatANNResultIds)
@interface PatANNResultIdsObjC : NSObject

@property (nonatomic, assign) int32_t count;
@property (nonatomic, assign) int32_t outputs;
@property (nonatomic, assign) int32_t alloced;
@property (nonatomic, strong, nullable) NSArray<NSNumber *> *ids;

@end

NS_SWIFT_NAME(PatANNResultDistances)
@interface PatANNResultDistsObjC : NSObject

@property (nonatomic, assign) int32_t count;
@property (nonatomic, assign) int32_t alloced;
@property (nonatomic, strong, nullable) NSArray<NSNumber *> *distances;

@end

NS_SWIFT_NAME(PatANNFloatData)
@interface PatANNFloatDataObjC : NSObject

@property (nonatomic, assign) int32_t count;
@property (nonatomic, assign) int32_t alloced;
@property (nonatomic, strong, nullable) NSArray<NSNumber *> *data;

@end

NS_SWIFT_NAME(PatANNShardConfig)
@interface PatANNShardConfigObjC : NSObject

@property (nonatomic, assign) uint32_t total;
@property (nonatomic, assign) uint32_t shardId;
@property (nonatomic, strong, nullable) NSString *path;

@end

NS_SWIFT_NAME(PatANNIDs)
@interface PatANNIDsObjC : NSObject

@property (nonatomic, assign) uint32_t start;
@property (nonatomic, assign) uint32_t end;

@end

// Enum types
typedef NS_ENUM(NSInteger, PatANNDataType) {
    PatANNDataTypeUnnormalized = 0,
    PatANNDataTypeNormalized = 1
} NS_SWIFT_NAME(PatANN.DataType);

typedef NS_ENUM(NSInteger, PatANNDistanceType) {
    PatANNDistanceTypeL2Square = 0,
    PatANNDistanceTypeL2,
    PatANNDistanceTypeCosine,
    PatANNDistanceTypeInnerProduct,
    PatANNDistanceTypeL1
} NS_SWIFT_NAME(PatANN.DistanceType);

@class PatANNQueryObjC;

// Protocol for query listener
NS_SWIFT_NAME(PatANNQueryListener)
@protocol PatANNQueryListenerObjC <NSObject>

@required
- (int)patANNOnFilter:(PatANNQueryObjC *)query id:(uint32_t)vectorId;
- (int)patANNOnResult:(PatANNQueryObjC *)query;

@end

// Wrapper for PatANNQuery
NS_SWIFT_NAME(PatANNQuery)
@interface PatANNQueryObjC : NSObject

- (void)destroy;
- (void)setListener:(nullable id<PatANNQueryListenerObjC>)listener enableFilter:(int)enableFilter;
- (void)setUserData:(nullable void *)data;
- (nullable void *)getUserData;
- (int)setRadius:(int)radius;
- (int)query:(nonnull NSArray<NSNumber *> *)vector k:(int)k;
- (int)more;
- (int)refine;
- (int)filter:(uint32_t)vectorId;
- (nonnull NSArray<NSNumber *> *)getResults;
- (nonnull NSArray<NSNumber *> *)getResultDists;

@end

// Wrapper for PatANNUtils
NS_SWIFT_NAME(PatANNUtils)
@interface PatANNUtilsObjC : NSObject

+ (nonnull PatANNUtilsObjC *)instance;

- (void)printMemoryUsage:(nullable NSString *)name level:(int)level;
- (int)deleteFilesInDirectory:(nullable NSString *)directory ageInSeconds:(int)ageInSeconds extension:(nullable NSString *)extension reverse:(int)reverse;
- (uint32_t)getRandom32;
- (uint32_t)getRandom32Max:(uint32_t)max;
- (uint64_t)getRandom64;
- (double)getRandom;

@end

// Main PatANN interface wrapper
NS_SWIFT_NAME(PatANN)
SYMBOL_EXPORT @interface PatANNObjC : NSObject

// Factory methods
+ (nonnull PatANNObjC *)createInstance:(int)dim;
+ (nonnull PatANNObjC *)createOnDiskInstance:(int)dim path:(nullable NSString *)path name:(nullable NSString *)name;
+ (int)interfaceVersion;

- (void)destroy;
- (void)thisIsPreproductionSoftware:(int)agree;
- (void)validateParameters:(int)validate;
- (void)syncToDisk:(uint32_t)interval;
- (void)setAllocationUnits:(uint32_t)units;
- (void)enableDiskCache:(uint64_t) size;
- (void)testDiskPerformance:(nullable NSString *)path blockSize:(uint32_t)blockSize fileSize:(uint32_t)fileSize duration:(int)duration forced:(int)forced;
- (void)enableHugePages:(int)enable;
- (void)setQuantization:(int)algo;
- (void)setQuantizationThreshold:(float)threshold;
- (void)setPatternProbes:(int)probes;
- (int)setConstellationSize:(int)size;
- (int)setRadius:(int)radius forLevel:(int)level;
- (void)setThreads:(int)threads;
- (void)setQueryThreads:(int)threads maxQueue:(int)maxQueue;
- (void)setIndexOptimization:(int)val;
- (void)setSearchOptimization:(int)val;
- (void)setDistanceType:(PatANNDistanceType)distanceType;
- (void)setMipsMode;
- (void)setNormalize:(int)enable;
- (void)enableDuplicateDetection:(int)level;
- (uint32_t)isIndexed:(nonnull NSArray<NSNumber *> *)vector;
- (void)destroyIndexOnDelete:(int)destroy;
- (uint32_t)isDuplicate:(nonnull NSArray<NSNumber *> *)vector threshold:(float)threshold;
- (void)setDuplicateThreshold:(int)enable threshold:(float)threshold overwrite:(int)overwrite;
- (uint32_t)addVector:(nonnull NSArray<NSNumber *> *)vector dimension:(int)dim mask:(uint64_t)mask;
- (void)deleteVector:(uint32_t)vectorId undelete:(int)undelete;
- (void)deleteVectors:(nonnull NSArray<NSNumber *> *)ids count:(int)count undelete:(int)undelete;
- (void)waitForIndexReady;
- (BOOL)isIndexReady;
- (nonnull PatANNQueryObjC *)createQuerySession:(int)radius count:(int)count;
- (float)distance:(nonnull NSArray<NSNumber *> *)v1 vector2:(nonnull NSArray<NSNumber *> *)v2;
- (float)distanceId:(uint32_t)id vector:(nonnull NSArray<NSNumber *> *)v;
- (void)normalizeVector:(nonnull NSMutableArray<NSNumber *> *)vector dimension:(int)dim;

@end

NS_ASSUME_NONNULL_END
