//
//  SimuNaviController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/7.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "SimuNaviController.h"

@interface SimuNaviController()

@end

@implementation SimuNaviController
- (void) startNavi
{
    // get Information of navigation
    TNKSearchNaviPoi *start = [[TNKSearchNaviPoi alloc] init];
    CLLocationCoordinate2D startPoi = {39.9842, 116.3074};
    start.coordinate = startPoi;
    
    TNKSearchNaviPoi *dest  = [[TNKSearchNaviPoi alloc] init];
    CLLocationCoordinate2D endPoi = {39.9852, 116.3144};
    dest.coordinate = endPoi;
    
    TNKCarRouteSearchOption *option = [[TNKCarRouteSearchOption alloc] init];
    option.avoidTrafficJam = YES;
    option.startRoadType = TNKRoadType_MainRoad;
    
    TNKCarRouteSearchRequest *request = [[TNKCarRouteSearchRequest alloc] init];
    request.startPoint = start;
    request.destinationPoint = dest;
    request.searchOption = option;
    

    [self.carManager searchNavigationRoutesWithRequest:request completion:^(TNKCarRouteSearchResult *result, NSError *error) {
        if(error == nil)
        {
            [self.carManager startSimulateWithIndex:0 locationEntry:nil];
            //            [self.carManager startSimulateWithIndex:0 locationEntry:nil];
        }
    }];
}

//- (void)buttonPrint
//{
////    self.naviView.TNKCarNaviFixCarProportion2D = CGPointMake(0.35, 0.65);
////    self.naviView.TNKCarNaviFixCarProportion3D = CGPointMake(0.35, 0.65);
//    self.naviView.hideNavigationPanel = YES;
//    [self.carManager stop];
//    [self.naviView clearAllRouteUI];
//}

- (void)carNavigationManagerDidArriveDestination:(TNKCarNaviManager *)manager
{
    
    [self.carManager unregisterUIDelegate:self.naviView];
    
    [self.carManager stop];
}

#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self startNavi];
    
}

- (void)dealloc
{
    [self.carManager stop];
}
@end
