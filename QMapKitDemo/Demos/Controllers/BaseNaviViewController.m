//
//  BaseNaviViewController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/6.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "BaseNaviViewController.h"
#import <TNKNavigationKit/TNKCarRouteSearchTypes.h>
#import <TNKNavigationKit/TNKCarNaviView.h>
#import <TNKNavigationKit/TNKCarNaviView.h>

@interface BaseNaviViewController()

@property (nonatomic, strong, readwrite) TNKCarNaviView *naviView;
@property (nonatomic, strong, readwrite) TNKCarNaviManager *carManager;

@end

@implementation BaseNaviViewController

- (void) setupSDK
{
    self.carManager = [[TNKCarNaviManager alloc] init];
    [self.carManager registerNaviDelegate:self];
    self.carManager.enableEnlargedIntersection = YES;
    self.carManager.enableGuidedLane = YES;
    
    self.naviView = [[TNKCarNaviView alloc] initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width,  self.view.bounds.size.height - 64)];
    self.naviView.mode = TNKCarNaviUIMode3DCarTowardsUp;
    self.naviView.hideNavigationPanel = NO;
    self.naviView.TNKCarNaviFixCarProportion2D = CGPointMake(0.5, 0.5);
    self.naviView.TNKCarNaviFixCarProportion3D = CGPointMake(0.5, 0.5);
    self.naviView.routeLineEraseType = 0;
    
    self.naviView.naviMapView.delegate = self;
    
    [self.carManager registerUIDelegate:self.naviView];
    
    [self.view addSubview:self.naviView];
}

#pragma mark - Life Cycle
- (void)viewDidLoad
{
    [super viewDidLoad];
    [self setupSDK];
}

@end
