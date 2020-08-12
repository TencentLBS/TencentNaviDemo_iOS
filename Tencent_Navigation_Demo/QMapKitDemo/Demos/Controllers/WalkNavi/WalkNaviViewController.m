//
//  WalkNaviViewController.m
//  QMapKitDemo
//
//  Created by ikaros on 2020/8/12.
//  Copyright © 2020 tencent. All rights reserved.
//

#import "WalkNaviViewController.h"

@interface WalkNaviViewController ()
@property (nonatomic, strong)  TNKWalkNaviView *walkNaviView;
@property (nonatomic, strong)  TNKWalkNaviManager *walkNaviManager;
@end

@implementation WalkNaviViewController

#pragma mark - Life Cycle
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self setupWalkSDK];
    [self startNavi];
}

- (void)dealloc {
    [self.walkNaviManager stop];
}


#pragma mark - Setups
- (void)setupWalkSDK {
    self.walkNaviManager = [[TNKWalkNaviManager alloc] init];

    self.walkNaviView = [[TNKWalkNaviView alloc] initWithFrame:self.view.bounds];
    self.walkNaviView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    self.walkNaviView.externalEdgeInsets = UIEdgeInsetsMake(220, 40, 160, 40);
    self.walkNaviView.delegate = self;
    self.walkNaviView.naviMapView.delegate = self;
    self.walkNaviView.showUIElements = YES;
    
    [self.view addSubview:self.walkNaviView];
    [self.walkNaviManager registerNaviDelegate:self.walkNaviView];
    [self.walkNaviManager registerNaviDelegate:self];
    

}

- (void)startNavi {
    TNKSearchNaviPoi *start = [[TNKSearchNaviPoi alloc] init];
    CLLocationCoordinate2D startPoi = {39.9842, 116.3074};
    start.coordinate = startPoi;
    
    TNKSearchNaviPoi *dest  = [[TNKSearchNaviPoi alloc] init];
    CLLocationCoordinate2D endPoi = {39.9852, 116.3144};
    dest.coordinate = endPoi;
    
    TNKWalkRouteSearchRequest *request = [[TNKWalkRouteSearchRequest alloc] init];
    request.startPoint = start;
    request.destinationPoint = dest;
    
    [self.walkNaviManager searchNaviRoutesWithRequest:request completion:^(TNKWalkRouteSearchResponse * _Nullable searchResponse, NSError * _Nullable error) {
        if (error == nil) {
            [self.walkNaviManager startSimulateWithIndex:0 locationEntry:nil];
        }
    }];
}

- (void)walkNaviViewCloseButtonClicked:(TNKWalkNaviView *)walkNaviView {
     [self.walkNaviManager stop];
    [self.navigationController popViewControllerAnimated:YES];
}

@end
