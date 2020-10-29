//
//  NavigationViewController.m
//  TNKNavigation
//
//  Created by tabsong on 2018/4/12.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import "NavigationViewController.h"
#import "SVProgressHUD.h"
#import <TNKNavigationKit/TNKNavigationKit.h>

#define kTrafficStatusBarHeight 10

@interface NavigationViewController ()
<TNKCarNaviUIDelegate,
TNKCarNaviViewDelegate,
TNKCarNaviViewDataSource,
QMapViewDelegate,
TNKCarNaviDelegate
>

@property (nonatomic, strong) TNKCarNaviManager *carNaviManager;
@property (nonatomic, assign) BOOL simulateLocation;
@property (nonatomic, assign) NSUInteger routeIndex;
@property (nonatomic, strong) TNKCarNaviView *carNaviView;

@end

@implementation NavigationViewController


#pragma mark - Life Cycle

- (instancetype)initWithCarNaviManager:(TNKCarNaviManager *)carNaviManager routeIndex:(NSUInteger)routeIndex simulateLocation:(BOOL)simulation
{
    NSParameterAssert(carNaviManager != nil);
    if (self = [super init])
    {
        self.carNaviManager = carNaviManager;
        [self.carNaviManager registerNaviDelegate:self];
        
        self.simulateLocation  = simulation;
        self.routeIndex = routeIndex;
        
        self.title = @"驾车导航";
    }
    
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self setupNaviView];
        
    [self startNavi];
    
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    [self.navigationController setToolbarHidden:YES animated:animated];
    [self.navigationController setNavigationBarHidden:YES];
}

- (void)dealloc
{
    [self stopNavi];
}

- (UIStatusBarStyle)preferredStatusBarStyle
{
    return UIStatusBarStyleDefault;
}

#pragma mark - Setup

- (void)setupNaviView
{
    // 构建UI.
    self.carNaviView = [[TNKCarNaviView alloc] initWithFrame:self.view.bounds];
    self.carNaviView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    
    self.carNaviView.delegate = self;
    self.carNaviView.dataSource = self;
    
//    self.carNaviView.mode = TNKCarNaviUIModeOverview;
//    self.carNaviView.nonOverviewNaviUIMode = TNKCarNaviUIMode2DMapTowardsNorth;
//    self.carNaviView.externalEdgeInsets = UIEdgeInsetsMake(220, 40, 160, 40);
    self.carNaviView.naviMapView.delegate = self;
    //self.carNaviView.mode = TNKCarNaviUIModeOverview;
    //self.carNaviView.dayNightMode = TNKCarNaviDayNightModeAlwaysNight;
    [self.carNaviView setShowTraffic:YES];
    self.carNaviView.showUIElements = YES;
//    self.carNaviView.showLimitSpeedAndCurrentRoadNameView = NO;
    [self.carNaviView setShowRoadTypeButton:YES];
    self.carNaviView.autoScaleEnabled = YES;

//    [self.carNaviView setVectorLineColor:[UIColor whiteColor]];
//    [self.carNaviView setShowVectorLineEnabled:NO];
//    self.carNaviView.hideNavigationPanel = YES;
    //self.carNaviView.guidedLaneEnabled = NO;
    //self.carNaviView.enlargedIntersectionEnabled = NO;
    
//    [self.carNaviView setShowVectorLineEnabled:NO];
    
//    TNKEndPointMarkerPresentation *endPointMarker = [[TNKEndPointMarkerPresentation alloc] init];
//    endPointMarker.diskIcon = [UIImage imageNamed:@"compass"];
//    endPointMarker.bubbleIcon = [UIImage imageNamed:@"ic_car_point"];
//    [self.carNaviView configEndPointMarkerPresentation:endPointMarker];
    
//    TNKStartPointMarkerPresentation *startPointMarker = [[TNKStartPointMarkerPresentation alloc] init];
////    startPointMarker.diskIcon = [UIImage imageNamed:@"compass"];
//    startPointMarker.bubbleIcon = [UIImage imageNamed:@"route_ic_wayPoint"];
//    [self.carNaviView configStartPointMarkerPresentation:startPointMarker];
    
//    
//    TNKWayPointMarkerPresentation *wayPointMarker = [[TNKWayPointMarkerPresentation alloc] init];
//    wayPointMarker.bubbleIcon = [UIImage imageNamed:@"route_ic_wayPoint"];
//    TNKWayPointMarkerPresentation *wayPointMarker1 = [[TNKWayPointMarkerPresentation alloc] init];
//    wayPointMarker1.bubbleIcon = [UIImage imageNamed:@"ic_car_point"];
//    [self.carNaviView configWayPointMarkerPresentation:@[wayPointMarker,wayPointMarker1, wayPointMarker]];
    
    [self.view addSubview:self.carNaviView];
}

- (void)startNavi
{
    // 绑定到Navi上.
    
    [self.carNaviManager registerUIDelegate:self.carNaviView];
    [self.carNaviManager registerUIDelegate:self];

    
    // 启动导航.
    if (self.simulateLocation)
    {
        NSString *filePath = [[NSBundle mainBundle] pathForResource:@"区间测速_case1_方案1_80" ofType:@"gps"];

        TNKGPSFileLocationManager *manager = [[TNKGPSFileLocationManager alloc] initWithFilePath:filePath];
        manager.rate = 1;
        
        [self.carNaviManager startSimulateWithIndex:self.routeIndex locationEntry:nil];
    }
    
    else
    {
        [self.carNaviManager startWithIndex:self.routeIndex];
    }
}

- (void)stopNavi
{
    [self.carNaviManager unregisterUIDelegate:self.carNaviView];
    [self.carNaviManager unregisterUIDelegate:self];

    [self.carNaviManager stop];
}


#pragma mark - TNKCarNaviViewDataSource

- (NSArray<id<TNKRemainingOverviewData>> *)remainingOverviewDataForCarNaviView:(TNKCarNaviView *)carNaviView
{
    //    TNKCoordinatePoint *data = [[TNKCoordinatePoint alloc] init];
    //    data.coordinate = CLLocationCoordinate2DMake(39.975951,116.317612);
    //
    //    return @[data];
    
    return nil;
}

#pragma mark - TNKCarNaviViewDelegate

- (void)carNaviView:(TNKCarNaviView *)carNaviView didChangeUIMode:(TNKCarNaviUIMode)mode
{
    NSLog(@"%s mode = %ld", __FUNCTION__, (long)mode);
    
}

- (void)carNaviView:(TNKCarNaviView *)carNaviView didChangeDayNightStatus:(TNKCarNaviDayNightStatus)status
{
    NSLog(@"%s status = %ld", __FUNCTION__, (long)status);
}

- (void)carNaviViewCloseButtonClicked:(TNKCarNaviView *)carNaviView  {
    [self stopNavi];
    [self.navigationController popViewControllerAnimated:YES];
}

#pragma mark - TNKCarNaviUIDelegate

- (void)carNavigationManagerDidGPSSignalBecomeWeak:(TNKCarNaviManager *)manager
{
    NSLog(@"gps weak");
    
}

- (void)carNavigationManagerDidGPSSignalBecomeStrong:(TNKCarNaviManager *)manager
{
    NSLog(@"gps strong");
    
}
- (void)carNavigationManager:(TNKCarNaviManager *)manager updateNavigationData:(TNKCarNavigationData *)data
{
    
   
    
//    int index = 0;
//    for (TNKNaviToWayPointInfo *wayPointInfo in data.wayPointsInfo) {
//        NSLog(@"wayPointInfo.index = %d, time = %d, distance = %d, poinxIndex = %d", index, wayPointInfo.remainingTime, wayPointInfo.remainingDistance, wayPointInfo.wayPointIndex);
//        index++;
//    }
}

- (void)carNavigationManager:(TNKCarNaviManager *)manager didArriveWaypoint:(int)index {
    NSLog(@"didArriveWaypoint=%d", index);
}

- (void)carNavigationManager:(TNKCarNaviManager *)manager updateRouteTrafficStatus:(TNKRouteTrafficStatus *)status
{
}

- (void)carNavigationManager:(TNKCarNaviManager *)manager didUpdateRoadType:(TNKRoadType)type
{

}

- (void)carNavigationManager:(TNKCarNaviManager *)manager didUpdateLocation:(TNKLocation *)location
{
    if(CLLocationCoordinate2DIsValid(location.matchedCoordinate))
    {
        //NSLog(@"matched coordinate: <%f,%f> timestamp: %f",location.matchedCoordinate.latitude, location.matchedCoordinate.longitude, [location.location.timestamp timeIntervalSince1970]);
    }
}

- (void)carNavigationManagerDidArriveDestination:(TNKCarNaviManager *)manager {
    // 到达终点回调。如果开发者未结束导航。这个方法可能执行多次
    
    //[self.carNaviManager stop];
}

@end
