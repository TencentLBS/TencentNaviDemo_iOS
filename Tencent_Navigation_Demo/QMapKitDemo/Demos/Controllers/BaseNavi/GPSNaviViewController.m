//
//  GPSNaviViewController.m
//  QMapKitDemo
//
//  Created by ikaros on 2020/11/3.
//  Copyright © 2020 tencent. All rights reserved.
//

#import "GPSNaviViewController.h"

@interface GPSNaviViewController ()

@end

@implementation GPSNaviViewController

#pragma mark - Life Cycle
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self startNavi];
}

- (void)dealloc
{
    [self.carManager stop];
}

#pragma mark - Private
- (void)startNavi {
    
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
            // 可以通过给定的GPS文件进行测试导航，可以测试偏航场景
            // 初始化GPS模拟导航manager. 文件格式定义如下:
            // 每个定位数据元素占一行,共有按序排列的八个属性,以逗号分隔,最后一个数据后不带逗号.
            // 八个属性为:经度,纬度,水平精度,角度,速度,时间,时间戳,海拔高度.
            //  例: 116.308086,39.983521,30,313.94,1.72,2014-6-10 11:17:5,1402370225.698,96
            NSString *filePath = [[NSBundle mainBundle] pathForResource:@"ios_traffic_time" ofType:@"gps"];

            TNKGPSFileLocationManager *manager = [[TNKGPSFileLocationManager alloc] initWithFilePath:filePath];
            manager.rate = 1;
            [self.carManager startSimulateWithIndex:0 locationEntry:manager];
        }
    }];
}

@end
