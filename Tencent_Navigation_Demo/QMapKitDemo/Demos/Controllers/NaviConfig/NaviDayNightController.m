//
//  NaviDayNightController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/8.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "NaviDayNightController.h"

@interface NaviDayNightController()
@property UISegmentedControl* segment;
@end

@implementation NaviDayNightController
- (void) addSeg
{
    NSArray *arr = [[NSArray alloc] initWithObjects:@"自动", @"日间", @"夜间", nil];
    self.segment = [[UISegmentedControl alloc] initWithItems:arr];
    self.segment.frame = CGRectMake(self.naviView.frame.size.width - 130.0f, 8.0f, 120.0f, 30.0f);
    [self.navigationController.navigationBar addSubview:self.segment];
    [self.segment addTarget:self action:@selector(selected:) forControlEvents:UIControlEventAllEvents];
}

-(void)selected:(id)sender
{
    UISegmentedControl *control = (UISegmentedControl*)sender;
    switch (control.selectedSegmentIndex) {
//            TNKCarNaviDayNightModeAuto        = 0,    ///< 自动切换
//            TNKCarNaviDayNightModeAlwaysDay   = 1,    ///< 始终白天
//            TNKCarNaviDayNightModeAlwaysNight = 2     ///< 始终黑夜
        case 0:
            self.naviView.dayNightMode = TNKCarNaviDayNightModeAuto;
            break;
        case 1:
            self.naviView.dayNightMode = TNKCarNaviDayNightModeAlwaysDay;
            break;
        case 2:
            self.naviView.dayNightMode = TNKCarNaviDayNightModeAlwaysNight;
            break;
        default:
            break;
    }
}

#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self addSeg];
    
}


-(void)viewWillDisappear:(BOOL)animated
{
    [self.segment removeFromSuperview];
    [super viewWillDisappear:animated];
}
@end
