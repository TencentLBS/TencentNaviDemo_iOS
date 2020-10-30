//
//  NaviDayNightController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/8.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "NaviRouteWidthController.h"

@interface NaviRouteWidthController()
@property UISlider* slider;
@end

@implementation NaviRouteWidthController
- (void) addSeg
{
    self.slider = [[UISlider alloc] initWithFrame:CGRectMake(self.naviView.frame.size.width - 130.0f, 8.0f, 110.0f, 30.0f)];
    self.slider.minimumValue = 8;
    self.slider.maximumValue = 20;
    [self.navigationController.navigationBar addSubview:self.slider];
    [self.slider addTarget:self action:@selector(sliderChanged:) forControlEvents:UIControlEventAllEvents];
}

-(void)sliderChanged:(id)sender
{
    UISlider *slider = (UISlider*)sender;
    self.naviView.routeLineWidth = slider.value;
}

#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self addSeg];
    
}


-(void)viewWillDisappear:(BOOL)animated
{
    [self.slider removeFromSuperview];
    [super viewWillDisappear:animated];
}
@end
