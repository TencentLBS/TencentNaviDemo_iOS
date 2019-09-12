//
//  QMSSearchOption.h
//  QMapSearchKit
//
//  Created by xfang on 14/11/5.
//  Copyright (c) 2014年 tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

/*!
 *  @brief 检索参数的基类
 */
@interface QMSSearchOption : NSObject

@end

#pragma mark -

@interface QMSPoiSearchOption : QMSSearchOption

/*!
 *  @brief  每页条目数，最大限制为20条。 默认10条
 */
@property (nonatomic, assign) NSUInteger page_size;

/*!
 *  @brief  第x页，默认第1页
 */
@property (nonatomic, assign) NSUInteger page_index;

/*!
 *  @brief 必填 POI搜索关键字，用于全文检索字段   例如:keyword=酒店 
 */
@property (nonatomic, copy) NSString *keyword;

/*!
 *  @brief  搜索地理范围, 语法参考:http://lbs.qq.com/webservice_v1/guide-search.html#boundary_detail , 
 *
 *  本接口提供更灵活的参数组合能力
     示例1，指定地区名称，不自动扩大范围：boundary=region(北京,0) 或者boundary=region(北京,0,39.9018,116.94038) 等
     示例2，周边搜索（圆形范围）：boundary=nearby(39.908491,116.374328,1000) 或者 boundary=nearby(39.908491,116.374328,1000,0) 等
     示例3，矩形区域范围：boundary=rectangle(39.9072,116.3689,39.9149,116.3793)
 
     SDK提供快捷构建该属性的方法
 */
@property (nonatomic, copy) NSString *boundary;

/*!
 *  @brief  指定地区名称
 *
 *  @param cityName     检索区域名称， 城市名字，如北京市。
 *  @param isAutoEntend 当前城市搜索无结果，是否自动扩大范围。 取值1：自动扩大范围; 取值0：仅在当前城市搜索。
 */
- (void)setBoundaryByRegionWithCityName: (NSString *)cityName autoExtend:(BOOL)isAutoEntend;

/*!
 *  @brief  指定地区名称
 *
 *  @param cityName     检索区域名称， 城市名字，如北京市。
 *  @param isAutoEntend 当前城市搜索无结果，是否自动扩大范围。 取值1：自动扩大范围; 取值0：仅在当前城市搜索。
 *  @param coordinate 搜索的建议中心点。当用户使用泛关键词搜索时（如酒店、超市），这类搜索多为了查找附近，使用此参数，搜索结果以此坐标为中心，返回就近地点，体验更优。
 */
- (void)setBoundaryByRegionWithCityName: (NSString *)cityName autoExtend:(BOOL)isAutoEntend center:(CLLocationCoordinate2D)coordinate;

/*!
 *  @brief  周边搜索  圆形区域范围
 *
 *  @param centerCoordinate  中心坐标
 *  @param radius            半径/米
 *  @param isAutoEntend 当前范围无结果时，是否自动扩大范围。 取值1：自动扩大范围; 取值0：不扩大。
 */
- (void)setBoundaryByNearbyWithCenterCoordinate:(CLLocationCoordinate2D)centerCoordinate radius:(NSUInteger)radius autoExtend:(BOOL)isAutoEntend;

/*!
 *  @brief  矩形范围
 *
 *  @param leftBottomCoordinate 左下/西南 坐标
 *  @param rightTopCoordinate   右上/东北 坐标
 */
- (void)setBoundaryByRectangleWithleftBottomCoordinate:(CLLocationCoordinate2D)leftBottomCoordinate rightTopCoordinate:(CLLocationCoordinate2D)rightTopCoordinate;

/*!
 *  @brief  筛选条件 
 
     搜索指定分类
     例如传入“category=公交站”则最终会被组装为filter=category=公交站
 
     搜索多个分类
     举例：category=大学,中学
 
     腾讯地图POI分类关键词参考: http://lbs.qq.com/webservice_v1/guide-appendix.html
 
     SDK提供快捷构建该属性的方法
 */
@property (nonatomic, copy) NSString *filter;

/*!
 *  @brief  构建filter
 *
 *  @param categories 为数组，最多支持5个分类词，会影响filter的值
 */
- (void)setFilterByCategories:(NSArray<NSString *> *)categories;

/*!
 *  @brief  排序方式：
 *          排序，目前仅周边搜索（boundary=nearby）
 *          支持按距离由近到远排序，默认取值取值：_distance, 以到boundary的中心点距离排序；当orderby为空时, 以POI权重排序
 */
@property (nonatomic, copy) NSString *orderby;

@end

#pragma mark -

@interface QMSSuggestionSearchOption : QMSSearchOption

/*!
 *  @brief 必填 用户输入的关键词（希望获取后续提示的关键词）	例如:keyword=南方
 */
@property (nonatomic, copy) NSString *keyword;

/*!
 *  @brief  设置城市名，限制关键词所示的地域范围，如，仅获取“广州市”范围内的提示内容	比如:region=广州
 */
@property (nonatomic, copy) NSString *region;

/*!
 *  @brief  筛选条件
 
     搜索指定分类
     例如传入“category=公交站”则最终组装为filter=category=公交站
     
     搜索多个分类
     举例：category=大学,中学
     
     腾讯地图POI分类关键词参考: http://lbs.qq.com/webservice_v1/guide-appendix.html
     
     SDK提供快捷构建该属性的方法
 */
@property (nonatomic, copy) NSString *filter;

/*!
 *  @brief  构建filter
 *
 *  @param categories 为数组，最多支持5个分类词，会影响filter的值
 */
- (void)setFilterByCategories:(NSArray<NSString *> *)categories;

/*!
 *  @brief  0：[默认]当前城市无结果时，自动扩大范围到全国匹配  1：固定在当前城市
 */
@property (nonatomic, copy) NSNumber *region_fix;

/*!
 *  @brief  定位坐标，传入后，若用户搜索关键词为类别词（如酒店、餐馆时），与此坐标距离近的地点将靠前显示，格式： location=lat,lng
 */
@property (nonatomic, copy) NSString *location;

/*!
 *  @brief  指定location经纬度
 *
 *  @param coordinate  位置坐标经纬度
 */
- (void)setLocationWithCoordinate:(CLLocationCoordinate2D)coordinate;

/*!
 *  @brief  是否返回子地点，如大厦停车场、出入口等
 *
 *  取值：
 *      0 [默认]不返回
 *      1 返回
 */
@property (nonatomic, copy) NSNumber *get_subpois;

/*!
 *  @brief  检索策略，
 *
 *  目前支持：
 *   policy=0：默认，常规策略
 *   policy=1：本策略主要用于收货地址、上门服务地址的填写，
 *   提高了小区类、商务楼宇、大学等分类的排序，过滤行政区、
 *   道路等分类（如海淀大街、朝阳区等），排序策略引入真实用户对输入提示的点击热度，
 *   使之更为符合此类应用场景，体验更为舒适
 *   policy=10：出行场景（网约车） – 起点查询
 *   policy=11：出行场景（网约车） – 终点查询
 */
@property (nonatomic, copy) NSNumber *policy;

/*!
 *  @brief  可选值：short   返回“不带行政区划的”短地址
 */
@property (nonatomic, copy) NSString *address_format;

/*!
 *  @brief  页码，从1开始，最大页码需通过count进行计算，必须与page_size同时使用
 */
@property (nonatomic, copy) NSNumber *page_index;

/*!
 *  @brief  每页条数，取值范围1-20，必须与page_index 时使用
 */
@property (nonatomic, copy) NSNumber *page_size;

@end

#pragma mark -

@interface QMSReverseGeoCodeSearchOption : QMSSearchOption

/*!
 *  @brief  位置坐标，格式：
    location=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *location;

/*!
 *  @brief  指定location经纬度
 *
 *  @param centerCoordinate  位置坐标经纬度
 */
- (void)setLocationWithCenterCoordinate:(CLLocationCoordinate2D)centerCoordinate;

/*!
 *  @brief  用于控制POI列表：
 *
 *  1 poi_options=address_format=short
 *  返回短地址，缺省时返回长地址
 *  2 poi_options=radius=5000
 *  半径，取值范围 1-5000（米）
 *  3 poi_options=page_size=20
 *  每页条数，取值范围 1-20
 *  4 poi_options=page_index=1
 *  页码，取值范围 1-20
 *  注：分页时page_size与page_index参数需要同时使用
 *  5 poi_options=policy=1/2/3/4/5
 *  控制返回场景，
 *  policy=1[默认] 以地标+主要的路+近距离POI为主，着力描述当前位置；
 *  policy=2 到家场景：筛选合适收货的POI，并会细化收货地址，精确到楼栋；
 *  policy=3 出行场景：过滤掉车辆不易到达的POI(如一些景区内POI)，增加道路出入口、交叉口、大区域出入口类POI，排序会根据真实API大用户的用户点击自动优化。
 *  policy=4 社交签到场景，针对用户签到的热门地点进行优先排序。
 *  policy=5 位置共享场景，用户经常用于发送位置、位置分享等场景的热门地点优先排序
 *  6 poi_options=category=分类词1,分类词2，
 *  指定分类，多关键词英文逗号分隔；
 *  （支持类别参见：附录）
 *
 *  【单个参数写法示例】：
 *  poi_options=address_format=short
 *  【多个参数英文分号间隔，写法示例】：
 *  poi_options=address_format=short;radius=5000;
 *  page_size=20;page_index=1;policy=2
 */
@property (nonatomic, copy) NSString *poi_options;

/*!
 *  @brief  是否返回周边POI列表 默认不返回
 */
@property (nonatomic, assign) BOOL get_poi;

@end

#pragma mark -

@interface QMSGeoCodeSearchOption : QMSSearchOption

/*!
 *  @brief  必填	用于做地理编码的地址	 比如:address=北京市海淀区彩和坊路海淀西大街74号
 */
@property (nonatomic, copy) NSString *address;

/*!
 *  @brief  指定地址所属城市	例如:region=北京
 */
@property (nonatomic, copy) NSString *region;

@end

#pragma mark - 

/*!
 *  @brief 步行路线规划的检索参数
 */
@interface QMSWalkingRouteSearchOption : QMSSearchOption

/*!
 *  @brief  起点坐标 格式：
 *  from=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *from;

/*!
 *  @brief  以CLLocationCoordinate2D方式设置起点经纬度
 *
 *  @param coordinate 起点经纬度
 */
- (void)setFromCoordinate:(CLLocationCoordinate2D)coordinate;

/*!
 *  @brief  终点坐标 格式：
 *  to=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *to;

/*!
 *  @brief  以CLLocationCoordinate2D方式设置终点点经纬度
 *
 *  @param coordinate 终点经纬度
 */
- (void)setToCoordinate:(CLLocationCoordinate2D)coordinate;


@end

#pragma mark -

/*!
 *  @brief 轨迹点
 */
@interface QMSTrackPoint : QMSSearchOption

/*!
 *  @brief  经纬度
 */
@property (nonatomic, assign) CLLocationCoordinate2D    coordinate;

/*!
 *  @brief  速度：GPS速度，单位 米/秒，取不到传-1
 */
@property (nonatomic, assign) double    speed;

/*!
 *  @brief  精度：GPS精度, 单位毫米，取不到传-1
 */
@property (nonatomic, assign) double    accuracy;

/*!
 *  @brief  运动方向： gps方向，正北为0, 顺时针夹角，[0-360)，获取不到时传-1
 */
@property (nonatomic, assign) double    course;

/*!
 *  @brief  设备方向：正北为0, 顺时针夹角，[0-360)，取不到传-1
 */
@property (nonatomic, assign) double    heading;

/*!
 *  @brief  时间：定位获取该点的时间，Unix时间戳，取不到传0
 */
@property (nonatomic, assign) double    time;

@end

/*!
 *  @brief 驾车路线规划的策略类型
 */
typedef enum
{
    QMSDrivingRoutePolicyTypeLeastTime = 0,     //省时
    QMSDrivingRoutePolicyTypeLeastFee = 1,      //省钱
    QMSDrivingRoutePolicyTypeLeastDistance = 2, //距离最短
    QMSDrivingRoutePolicyTypeRealTraffic = 3,   //综合最优
} QMSDrivingRoutePolicyType;

/*!
 *  @brief 驾车路线规划的检索参数
 */
@interface QMSDrivingRouteSearchOption : QMSSearchOption

/*!
 *  @brief  起点坐标 格式：
 *  from=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *from;

/*!
 *  @brief  以CLLocationCoordinate2D方式设置起点经纬度
 *
 *  @param coordinate 起点经纬度
 */
- (void)setFromCoordinate:(CLLocationCoordinate2D)coordinate;

/*!
 *  @brief  起点POI ID，传入后，优先级高于from（坐标）
 *
 *  样例: 4077524088693206111
 */
@property (nonatomic, copy) NSString *from_poi;

/*!
 *  @brief  起点轨迹
 *
 *  可通过setTrackPoints生成. 格式样例：
 *      40.037029,116.316633,16,500,160,-1,1529491290;40.036634,116.317170,16,500,161,-1,1529491300;...
 */
@property (nonatomic, copy) NSString *from_track;

/*!
 *  @brief  设置起点轨迹
 *
 *  此方法会生成from_track的值
 *
 *  在真实的场景中，易受各种环境及设备精度影响，导致定位点产生误差，传入起点前段轨迹，可有效提升准确度。
 *  优先级：
 *  高于from参数
 *  轨迹中的每个定位点包含以下信息：
 *  1.纬度
 *  2.经度
 *  3.速度：GPS速度，单位 米/秒，取不到传-1
 *  4.精度：GPS精度, 单位毫米，取不到传-1
 *  5.运动方向： gps方向，正北为0, 顺时针夹角，[0-360)，获取不到时传-1
 *  6.设备方向：正北为0, 顺时针夹角，[0-360)，取不到传-1
 *  7.时间：定位获取该点的时间，Unix时间戳，取不到传0
 *  参数格式：
 *  1.轨迹中最多支持传入50个点。
 *  2.每个点之间英文分号分隔，时间顺序由旧到新（第一个点最早获取，最后一个点最新得到）
 *  3.每个点中的信息用英文逗号分隔，并按以下顺序传入：
 *  纬度,经度,速度,精度,运动方向,设备方向,时间;第2个点;第3个点……
 *  from=lat<纬度>,lng<经度>
 */
- (void)setTrackPoints:(NSArray<QMSTrackPoint *> *)points;

/*!
 *  @brief  终点坐标 格式：
 *  to=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *to;

/*!
 *  @brief  以CLLocationCoordinate2D方式设置终点点经纬度
 *
 *  @param coordinate 终点经纬度
 */
- (void)setToCoordinate:(CLLocationCoordinate2D)coordinate;

/*!
 *  @brief  终点POI ID（可通过腾讯位置服务地点搜索服务得到），当目的地为较大园区、小区时，会以引导点做为终点（如出入口等），体验更优。
 *
 *  该参数优先级高于to（坐标），但是当目的地无引导点数据或POI ID失效时，仍会使用to（坐标）作为终点
 *  样例: 4077524088693206111
 */
@property (nonatomic, copy) NSString *to_poi;

/*!
 *  @brief  路线规划条件
 
    参考一下枚举值:
    LEAST_TIME 表示速度优先，
    LEAST_FEE 表示费用优先，
    LEAST_DISTANCE 表示距离优先，
    REAL_TRAFFIC 表示根据实时路况计算最优路线，
 */
@property (nonatomic, copy) NSString *policy;

/*!
 *  @brief  枚举方式设置查询策略
 *
 *  @param type 查询策略
 */
- (void)setPolicyWithType:(QMSDrivingRoutePolicyType)type;

/*!
 *  @brief  途径点,元素类型为CLLocationCoordinate2D的NSValue类型
 */
@property (nonatomic, copy) NSString *waypoints;

/*!
 *  @brief  以CLLocationCoordinate2D数据方式设置途径点
 *
 *  @param coordinates 途经点数组
 *  @param count       数组长度
 */
- (void)setWayPointsWithCoordinates:(CLLocationCoordinate2D *)coordinates count:(NSUInteger)count;

/*!
 *  @brief  [from辅助参数]在起点位置时的车头方向，数值型，取值范围0至360（0度代表正北，顺时针一周360度）
 *
 *  传入车头方向，对于车辆所在道路的判断非常重要，直接影响路线计算的效果
 */
@property (nonatomic, assign) NSNumber    *heading;

/*!
 *  @brief  [from辅助参数]速度，单位：米/秒，默认3。 当速度低于1.39米/秒时，heading将被忽略
 */
@property (nonatomic, assign) NSNumber    *speed;

/*!
 *  @brief  [from辅助参数]定位精度，单位：米，取>0数值，默认5。 当定位精度>30米时heading参数将被忽略
 */
@property (nonatomic, assign) NSNumber    *accuracy;

/*!
 *  @brief  车牌号，填入后，路线引擎会根据车牌对限行区域进行避让，不填则不不考虑限行问题
 */
@property (nonatomic, copy) NSString *plate_number;

@end

#pragma mark - BusingRoute

/*!
 *  @brief 公交路线规划的策略类型
 */
typedef enum
{
    QMSBusingRoutePolicyTypeLeastTime = 0,          //省时
    QMSBusingRoutePolicyTypeLeastTransfer = 1,      //少换乘
    QMSBusingRoutePolicyTypeLeastWalking = 2,       //少步行
} QMSBusingRoutePolicyType;

/*!
 *  @brief 公交路线规划的检索参数
 */
@interface QMSBusingRouteSearchOption : QMSSearchOption

/*!
 *  @brief  起点坐标 格式：
 *  from=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *from;

/*!
 *  @brief  以CLLocationCoordinate2D方式设置起点经纬度
 *
 *  @param coordinate 起点经纬度
 */
- (void)setFromCoordinate:(CLLocationCoordinate2D)coordinate;

/*!
 *  @brief  终点坐标 格式：
 *  to=lat<纬度>,lng<经度>
 */
@property (nonatomic, copy) NSString *to;

/*!
 *  @brief  以CLLocationCoordinate2D方式设置终点点经纬度
 *
 *  @param coordinate 终点经纬度
 */
- (void)setToCoordinate:(CLLocationCoordinate2D)coordinate;

/*!
 *  @brief  路线规划优先条件
 *
 *  (非必填)
     1) 排序策略，以下三选一：
     policy=LEAST_TIME：时间短（默认）
     policy=LEAST_TRANSFER：少换乘
     policy=LEAST_WALKING：少步行
     2) 额外限制条件
     （可与排序策略配合使用，如：policy=LEAST_TRANSFER,NO_SUBWAY）：
     NO_SUBWAY ，不坐地铁
 */
@property (nonatomic, copy) NSString *policy;

/*!
 *  @brief  枚举方式设置查询策略
 *
 *  @param type 查询策略
 */
- (void)setPolicyWithType:(QMSBusingRoutePolicyType)type;

/*!
 *  @brief  出发时间
 *
 *  用于过滤掉非运营时段的线路，不传时默认使用当前时间(非必填)
 */
@property (nonatomic, copy) NSDate *departure_time;

@end

#pragma mark - QMSDistrictListSearchOption

/*!
 *  @brief 行政区划的检索参数基类
 */
@interface QMSDistrictBaseSearchOption : QMSSearchOption

@end

/*!
 *  @brief 行政区划列表的检索参数
 */
@interface QMSDistrictListSearchOption : QMSDistrictBaseSearchOption

@end

#pragma mark - QMSDistrictChildrenSearchOption

/*!
 *  @brief 获取子行政区划列表的检索参数
 */
@interface QMSDistrictChildrenSearchOption : QMSDistrictBaseSearchOption

/*!
 *  @brief  父级行政区划ID，缺省时则返回最顶级行政区划
 */
@property (nonatomic, copy) NSString *ID;

@end

#pragma mark - QMSDistrictSearchSearchOption

@interface QMSDistrictSearchSearchOption : QMSDistrictBaseSearchOption

/*!
 *  @brief  搜索关键词
 *
 *  1.支持输入一个文本关键词
 *  2.支持多个行政区划代码，英文逗号分隔
 */
@property (nonatomic, copy) NSString *keyword;

@end

