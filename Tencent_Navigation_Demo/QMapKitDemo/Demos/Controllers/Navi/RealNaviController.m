//
//  RealNaviController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/7.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "RealNaviController.h"

@interface RealNaviController()
@property BOOL flag;
@end

@implementation RealNaviController

- (void) startNavi
{
    // get Information of navigation
    
    TNKSearchNaviPoi *start = [[TNKSearchNaviPoi alloc] init];
    CLLocationCoordinate2D startPoi = {39.9842, 116.3074};
    start.coordinate = startPoi;
    
    TNKSearchNaviPoi *dest  = [[TNKSearchNaviPoi alloc] init];
    CLLocationCoordinate2D endPoi = {39.9930, 116.3376};
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
            [self.carManager startWithIndex:0];
        }
    }];
}


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
