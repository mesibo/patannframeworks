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

- (void)destroy NS_SWIFT_NAME(destroy());
- (void)setListener:(nullable id<PatANNQueryListenerObjC>)listener NS_SWIFT_NAME(setListener(_:));
- (nullable id<PatANNQueryListenerObjC>)getListener NS_SWIFT_NAME(getListener());
- (nonnull PatANNObjC *)getParent NS_SWIFT_NAME(getParent());
- (void)setUserData:(nullable id)userData NS_SWIFT_NAME(setUserData(_:));
- (nullable id)getUserData NS_SWIFT_NAME(getUserData());
- (NSInteger)setRadius:(NSInteger)radius NS_SWIFT_NAME(setRadius(_:));
- (BOOL)query:(nonnull NSArray<NSNumber *> *)vector k:(NSInteger)k NS_SWIFT_NAME(query(_:k:));
- (BOOL)more NS_SWIFT_NAME(more());
- (BOOL)refine NS_SWIFT_NAME(refine());
- (BOOL)filter:(NSInteger)vectorId NS_SWIFT_NAME(filter(_:));
- (nonnull NSArray<NSNumber *> *)getResults NS_SWIFT_NAME(getResults());
- (nonnull NSArray<NSNumber *> *)getResultDists NS_SWIFT_NAME(getResultDists());

@end

// Wrapper for PatANNUtils
NS_SWIFT_NAME(PatANNUtils)
@interface PatANNUtilsObjC : NSObject

+ (nonnull PatANNUtilsObjC *)instance NS_SWIFT_NAME(instance());

- (void)printMemoryUsage:(nullable NSString *)name level:(NSInteger)level NS_SWIFT_NAME(printMemoryUsage(_:level:));
- (NSInteger)deleteFilesInDirectory:(nullable NSString *)directory ageInSeconds:(NSInteger)ageInSeconds extension:(nullable NSString *)extension reverse:(NSInteger)reverse NS_SWIFT_NAME(deleteFilesInDirectory(_:ageInSeconds:extension:reverse:));
- (NSInteger)getRandom32 NS_SWIFT_NAME(getRandom32());
- (NSInteger)getRandom32Max:(NSInteger)max NS_SWIFT_NAME(getRandom32Max(_:));
- (NSInteger)getRandom64 NS_SWIFT_NAME(getRandom64());
- (double)getRandom NS_SWIFT_NAME(getRandom());

@end

// Main PatANN interface wrapper (matching PatANN.java)
NS_SWIFT_NAME(PatANN)
SYMBOL_EXPORT @interface PatANNObjC : NSObject

// Factory methods
+ (nonnull PatANNObjC *)createInstance:(NSInteger)dimension NS_SWIFT_NAME(createInstance(_:));
+ (nonnull PatANNObjC *)createOnDiskInstance:(NSInteger)dimension path:(nullable NSString *)path name:(nullable NSString *)name NS_SWIFT_NAME(createOnDiskInstance(_:path:name:));

// Instance methods
- (void)destroy NS_SWIFT_NAME(destroy());
- (void)this_is_preproduction_software:(BOOL)agree NS_SWIFT_NAME(this_is_preproduction_software(_:));
- (void)validateParameters:(BOOL)validate NS_SWIFT_NAME(validateParameters(_:));
- (void)setIndexListener:(nullable id<PatANNIndexListenerObjC>)listener count:(NSInteger)count NS_SWIFT_NAME(setIndexListener(_:count:));
- (void)setIndexListener:(nullable id<PatANNIndexListenerObjC>)listener NS_SWIFT_NAME(setIndexListener(_:));
- (nullable id<PatANNIndexListenerObjC>)getIndexListener NS_SWIFT_NAME(getIndexListener());
- (void)syncToDisk:(NSInteger)interval NS_SWIFT_NAME(syncToDisk(_:));
- (void)setAllocationUnits:(NSInteger)units NS_SWIFT_NAME(setAllocationUnits(_:));
- (void)enableDiskCache:(NSInteger)size NS_SWIFT_NAME(enableDiskCache(_:));
- (void)testDiskPerformance:(nullable NSString *)path blockSize:(NSInteger)blockSize fileSize:(NSInteger)fileSize duration:(NSInteger)duration forced:(BOOL)forced NS_SWIFT_NAME(testDiskPerformance(_:blockSize:fileSize:duration:forced:));
- (void)enableHugePages:(BOOL)enable NS_SWIFT_NAME(enableHugePages(_:));
- (void)setQuantization:(NSInteger)algo NS_SWIFT_NAME(setQuantization(_:));
- (void)setQuantizationThreshold:(float)threshold NS_SWIFT_NAME(setQuantizationThreshold(_:));
- (void)setPatternProbes:(NSInteger)probes NS_SWIFT_NAME(setPatternProbes(_:));
- (NSInteger)setConstellationSize:(NSInteger)size NS_SWIFT_NAME(setConstellationSize(_:));
- (NSInteger)setRadius:(NSInteger)radius NS_SWIFT_NAME(setRadius(_:));
- (void)setThreads:(NSInteger)threads NS_SWIFT_NAME(setThreads(_:));
- (void)setQueryThreads:(NSInteger)threads maxQueue:(NSInteger)maxQueue NS_SWIFT_NAME(setQueryThreads(_:maxQueue:));
- (void)setIndexOptimization:(NSInteger)val NS_SWIFT_NAME(setIndexOptimization(_:));
- (void)setSearchOptimization:(NSInteger)val NS_SWIFT_NAME(setSearchOptimization(_:));
- (void)setDistanceType:(PatANNDistanceType)distanceType NS_SWIFT_NAME(setDistanceType(_:));
- (void)setMipsMode NS_SWIFT_NAME(setMipsMode());
- (void)setNormalize:(BOOL)enable NS_SWIFT_NAME(setNormalize(_:));
- (void)enableDuplicateDetection:(NSInteger)level NS_SWIFT_NAME(enableDuplicateDetection(_:));
- (NSInteger)isIndexed:(nonnull NSArray<NSNumber *> *)vector NS_SWIFT_NAME(isIndexed(_:));
- (void)destroyIndexOnDelete:(BOOL)destroy NS_SWIFT_NAME(destroyIndexOnDelete(_:));
- (NSInteger)isDuplicate:(nonnull NSArray<NSNumber *> *)vector threshold:(float)threshold NS_SWIFT_NAME(isDuplicate(_:threshold:));
- (void)setDuplicateThreshold:(BOOL)enable threshold:(float)threshold overwrite:(BOOL)overwrite NS_SWIFT_NAME(setDuplicateThreshold(_:threshold:overwrite:));
- (NSInteger)addVector:(nonnull NSArray<NSNumber *> *)vector NS_SWIFT_NAME(addVector(_:));
- (void)deleteVector:(NSInteger)vectorId undelete:(BOOL)undelete NS_SWIFT_NAME(deleteVector(_:undelete:));
- (void)deleteVectors:(nonnull NSArray<NSNumber *> *)ids count:(NSInteger)count undelete:(BOOL)undelete NS_SWIFT_NAME(deleteVectors(_:count:undelete:));
- (void)waitForIndexReady NS_SWIFT_NAME(waitForIndexReady());
- (BOOL)isIndexReady NS_SWIFT_NAME(isIndexReady());
- (nonnull PatANNQueryObjC *)createQuerySession:(NSInteger)radius count:(NSInteger)count NS_SWIFT_NAME(createQuerySession(_:count:));
- (float)distance:(nonnull NSArray<NSNumber *> *)v1 vector2:(nonnull NSArray<NSNumber *> *)v2 NS_SWIFT_NAME(distance(_:vector2:));
- (float)distanceId:(NSInteger)id vector:(nonnull NSArray<NSNumber *> *)v NS_SWIFT_NAME(distanceId(_:vector:));
- (void)normalizeVector:(NSMutableArray<NSNumber *> *)vector dimension:(NSInteger)dimension NS_SWIFT_NAME(normalizeVector(_:dimension:));

@end

NS_ASSUME_NONNULL_END