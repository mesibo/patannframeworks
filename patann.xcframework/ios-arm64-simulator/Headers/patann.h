#import <Foundation/Foundation.h>

#ifdef SO_BUILD
  #define SYMBOL_EXPORT __attribute__((visibility("default")))
#else
  #define SYMBOL_EXPORT
#endif

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(PatANNResults)
@interface PatANNResultsObjC : NSObject

@property (nonatomic, assign) NSInteger count;
@property (nonatomic, assign) NSInteger alloced;
@property (nonatomic, assign) NSInteger mergeIndex;
@property (nonatomic, strong, nullable) NSArray<NSNumber *> *ids;  
@property (nonatomic, strong, nullable) NSArray<NSNumber *> *distances;

@end

NS_SWIFT_NAME(PatANNResultIds)
@interface PatANNResultIdsObjC : NSObject

@property (nonatomic, assign) NSInteger count;
@property (nonatomic, assign) NSInteger outputs;
@property (nonatomic, assign) NSInteger alloced;
@property (nonatomic, strong, nullable) NSArray<NSNumber *> *ids;

@end

NS_SWIFT_NAME(PatANNResultDistances)
@interface PatANNResultDistsObjC : NSObject

@property (nonatomic, assign) NSInteger count;
@property (nonatomic, assign) NSInteger alloced;
@property (nonatomic, strong, nullable) NSArray<NSNumber *> *distances;

@end

NS_SWIFT_NAME(PatANNFloatData)
@interface PatANNFloatDataObjC : NSObject

@property (nonatomic, assign) NSInteger count;
@property (nonatomic, assign) NSInteger alloced;
@property (nonatomic, strong, nullable) NSArray<NSNumber *> *data;

@end

NS_SWIFT_NAME(PatANNShardConfig)
@interface PatANNShardConfigObjC : NSObject

@property (nonatomic, assign) NSInteger total;
@property (nonatomic, assign) NSInteger shardId;
@property (nonatomic, strong, nullable) NSString *path;

@end

NS_SWIFT_NAME(PatANNIDs)
@interface PatANNIDsObjC : NSObject

@property (nonatomic, assign) NSInteger start;
@property (nonatomic, assign) NSInteger end;

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
@class PatANNObjC;

// Protocol for index listener (matching PatANNIndexListener.java)
NS_SWIFT_NAME(PatANNIndexListener)
@protocol PatANNIndexListenerObjC <NSObject>

@required
- (void)PatANNOnIndexUpdate:(PatANNObjC *)ann indexed:(NSInteger)indexed total:(NSInteger)total
NS_SWIFT_NAME(PatANNOnIndexUpdate(ann:indexed:total:));

@end

// Protocol for query listener (matching PatANNQueryListener.java)
NS_SWIFT_NAME(PatANNQueryListener)
@protocol PatANNQueryListenerObjC <NSObject>

@required
- (void)PatANNOnResult:(PatANNQueryObjC *)query NS_SWIFT_NAME(PatANNOnResult(query:));
@end

// Wrapper for PatANNQuery (matching PatANNQuery.java)
NS_SWIFT_NAME(PatANNQuery)
@interface PatANNQueryObjC : NSObject

- (void)destroy;
- (void)setListener:(nullable id<PatANNQueryListenerObjC>)listener;
- (nullable id<PatANNQueryListenerObjC>)getListener;
- (nonnull PatANNObjC *)getParent;
- (void)setUserData:(nullable id)userData;
- (nullable id)getUserData;
- (NSInteger)setRadius:(NSInteger)radius;
- (BOOL)query:(nonnull NSArray<NSNumber *> *)vector k:(NSInteger)k;
- (BOOL)more;
- (BOOL)refine;
- (BOOL)filter:(NSInteger)vectorId;
- (nonnull NSArray<NSNumber *> *)getResults;
- (nonnull NSArray<NSNumber *> *)getResultDists;

@end

// Wrapper for PatANNUtils
NS_SWIFT_NAME(PatANNUtils)
@interface PatANNUtilsObjC : NSObject

+ (nonnull PatANNUtilsObjC *)instance;

- (void)printMemoryUsage:(nullable NSString *)name level:(NSInteger)level;
- (NSInteger)deleteFilesInDirectory:(nullable NSString *)directory ageInSeconds:(NSInteger)ageInSeconds extension:(nullable NSString *)extension reverse:(NSInteger)reverse;
- (NSInteger)getRandom32;
- (NSInteger)getRandom32Max:(NSInteger)max;
- (NSInteger)getRandom64;
- (double)getRandom;

@end

// Main PatANN interface wrapper (matching PatANN.java)
NS_SWIFT_NAME(PatANN)
SYMBOL_EXPORT @interface PatANNObjC : NSObject

// Factory methods
+ (nonnull PatANNObjC *)createInstance:(NSInteger)dimension;
+ (nonnull PatANNObjC *)createOnDiskInstance:(NSInteger)dimension path:(nullable NSString *)path name:(nullable NSString *)name;

// Instance methods
- (void)destroy;
- (void)this_is_preproduction_software:(BOOL)agree;
- (void)validateParameters:(BOOL)validate;
- (void)setIndexListener:(nullable id<PatANNIndexListenerObjC>)listener count:(NSInteger)count;
- (void)setIndexListener:(nullable id<PatANNIndexListenerObjC>)listener;
- (nullable id<PatANNIndexListenerObjC>)getIndexListener;
- (void)syncToDisk:(NSInteger)interval;
- (void)setAllocationUnits:(NSInteger)units;
- (void)enableDiskCache:(NSInteger)size;
- (void)testDiskPerformance:(nullable NSString *)path blockSize:(NSInteger)blockSize fileSize:(NSInteger)fileSize duration:(NSInteger)duration forced:(BOOL)forced;
- (void)enableHugePages:(BOOL)enable;
- (void)setQuantization:(NSInteger)algo;
- (void)setQuantizationThreshold:(float)threshold;
- (void)setPatternProbes:(NSInteger)probes;
- (NSInteger)setConstellationSize:(NSInteger)size;
- (NSInteger)setRadius:(NSInteger)radius;
- (void)setThreads:(NSInteger)threads;
- (void)setQueryThreads:(NSInteger)threads maxQueue:(NSInteger)maxQueue;
- (void)setIndexOptimization:(NSInteger)val;
- (void)setSearchOptimization:(NSInteger)val;
- (void)setDistanceType:(PatANNDistanceType)distanceType;
- (void)setMipsMode;
- (void)setNormalize:(BOOL)enable;
- (void)enableDuplicateDetection:(NSInteger)level;
- (NSInteger)isIndexed:(nonnull NSArray<NSNumber *> *)vector;
- (void)destroyIndexOnDelete:(BOOL)destroy;
- (NSInteger)isDuplicate:(nonnull NSArray<NSNumber *> *)vector threshold:(float)threshold;
- (void)setDuplicateThreshold:(BOOL)enable threshold:(float)threshold overwrite:(BOOL)overwrite;
- (NSInteger)addVector:(nonnull NSArray<NSNumber *> *)vector;
- (void)deleteVector:(NSInteger)vectorId undelete:(BOOL)undelete;
- (void)deleteVectors:(nonnull NSArray<NSNumber *> *)ids count:(NSInteger)count undelete:(BOOL)undelete;
- (void)waitForIndexReady;
- (BOOL)isIndexReady;
- (nonnull PatANNQueryObjC *)createQuerySession:(NSInteger)radius count:(NSInteger)count;
- (float)distance:(nonnull NSArray<NSNumber *> *)v1 vector2:(nonnull NSArray<NSNumber *> *)v2;
- (float)distanceId:(NSInteger)id vector:(nonnull NSArray<NSNumber *> *)v;
- (void)normalizeVector:(NSMutableArray<NSNumber *> *)vector dimension:(NSInteger)dimension;

@end

NS_ASSUME_NONNULL_END
