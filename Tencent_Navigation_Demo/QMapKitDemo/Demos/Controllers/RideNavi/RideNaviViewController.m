//
//  RideNaviViewController.m
//  QMapKitDemo
//
//  Created by ikaros on 2020/8/12.
//  Copyright © 2020 tencent. All rights reserved.
//

#import "RideNaviViewController.h"

@interface RideNaviViewController ()
@property (nonatomic, strong)  TNKRideNaviView *rideNaviView;
@property (nonatomic, strong)  TNKRideNaviManager *rideNaviManager;
@end

@implementation RideNaviViewController

#pragma mark - Life Cycle
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self setupRideSDK];
    [self startNavi];
}

- (void)dealloc {
    [self.rideNaviManager stop];
}


#pragma mark - Setups
- (void)setupRideSDK {
    self.rideNaviManager = [[TNKRideNaviManager alloc] init];
    self.rideNaviManager.enableInternalTTS = YES;
    self.rideNaviView = [[TNKRideNaviView alloc] initWithFrame:self.view.bounds];
    self.rideNaviView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    self.rideNaviView.externalEdgeInsets = UIEdgeInsetsMake(220, 40, 160, 40);
    self.rideNaviView.delegate = self;
    self.rideNaviView.naviMapView.delegate = self;
    self.rideNaviView.showUIElements = YES;
    
    [self.view addSubview:self.rideNaviView];
    [self.rideNaviManager registerNaviDelegate:self.rideNaviView];
    [self.rideNaviManager registerNaviDelegate:self];
    

}

- (void)startNavi {
    TNKSearchNaviPoi *start = [[TNKSearchNaviPoi alloc] init];
    CLLocationCoordinate2D startPoi = {39.9842, 116.3074};
    start.coordinate = startPoi;
    
    TNKSearchNaviPoi *dest  = [[TNKSearchNaviPoi alloc] init];
    CLLocationCoordinate2D endPoi = {39.9852, 116.3144};
    dest.coordinate = endPoi;
    
    TNKRideRouteSearchRequest *request = [[TNKRideRouteSearchRequest alloc] init];
    request.startPoint = start;
    request.destinationPoint = dest;
    
    [self.rideNaviManager searchNaviRoutesWithRequest:request completion:^(TNKRideRouteSearchResponse * _Nullable searchResponse, NSError * _Nullable error) {
        if (error == nil) {
            [self.rideNaviManager startSimulateWithIndex:0 locationEntry:nil];
        }
    }];
}

- (void)rideNaviViewCloseButtonClicked:(TNKRideNaviView *)rideNaviView {
    [self.rideNaviManager stop];
    [self.navigationController popViewControllerAnimated:YES];
}

@end
