//
//  NaviModeController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/8.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "NaviModeController.h"

@interface NaviModeController()
@property UISegmentedControl* segment;
@end

@implementation NaviModeController
- (void) addSeg
{
    NSArray *arr = [[NSArray alloc] initWithObjects:@"3D", @"2D", @"全览", nil];
    self.segment = [[UISegmentedControl alloc] initWithItems:arr];
    self.segment.frame = CGRectMake(self.naviView.frame.size.width - 130.0f, 8.0f, 120.0f, 30.0f);
    [self.navigationController.navigationBar addSubview:self.segment];
    [self.segment addTarget:self action:@selector(selected:) forControlEvents:UIControlEventAllEvents];
}

-(void)selected:(id)sender
{
    UISegmentedControl *control = (UISegmentedControl*)sender;
    switch (control.selectedSegmentIndex) {
        case 0:
            self.naviView.mode = TNKCarNaviUIMode3DCarTowardsUp;
            break;
        case 1:
            self.naviView.mode = TNKCarNaviUIMode2DMapTowardsNorth;
            break;
        case 2:
            self.naviView.mode = TNKCarNaviUIModeOverview;
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
