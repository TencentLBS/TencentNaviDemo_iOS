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


@interface BaseNaviViewController()

@property (nonatomic, strong, readwrite) TNKCarNaviView *naviView;
@property (nonatomic, strong, readwrite) TNKCarNaviManager *carManager;

@end

@implementation BaseNaviViewController

- (void) setupSDK
{
    self.carManager = [[TNKCarNaviManager alloc] init];
    self.carManager.enableEnlargedIntersection = YES;
    self.carManager.enableGuidedLane = YES;
    self.carManager.enableInternalTTS = YES;
    self.edgesForExtendedLayout = UIRectEdgeNone;
    self.naviView = [[TNKCarNaviView alloc] initWithFrame:self.view.bounds];
    self.naviView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    self.naviView.mode = TNKCarNaviUIMode3DCarTowardsUp;
    self.naviView.hideNavigationPanel = NO;
    self.naviView.TNKCarNaviFixCarProportion2D = CGPointMake(0.5, 0.75);
    self.naviView.TNKCarNaviFixCarProportion3D = CGPointMake(0.5, 0.75);
    self.naviView.routeLineEraseType = 0;
    
    self.naviView.naviMapView.delegate = self;
    
    [self.view addSubview:self.naviView];
    
    [self.carManager registerUIDelegate:self.naviView];
    [self.carManager registerNaviDelegate:self];
}

#pragma mark - Life Cycle
- (void)viewDidLoad
{
    [super viewDidLoad];
    [self setupSDK];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self.navigationController setNavigationBarHidden:NO animated:animated];
    
}

@end
