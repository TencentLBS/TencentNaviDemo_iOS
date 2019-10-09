//
//  AddKitNaviController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/8.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "AddKitNaviController.h"

@interface AddKitNaviController()
@property(nonatomic, strong) UITextField *textView;
@property(nonatomic, strong) UITextField *textView2;
@end

@implementation AddKitNaviController

- (void)setupPanel
{
    self.textView = [[UITextField alloc] initWithFrame:CGRectMake(7, 160, 60, 60)];
    [self.textView setBackgroundColor:[UIColor whiteColor]];
    [self.textView.layer setBorderWidth:3.0];
    [self.textView.layer setBorderColor:[UIColor redColor].CGColor];
    [self.textView setFont:[UIFont boldSystemFontOfSize:25]];
    [self.textView setTextColor:[UIColor blackColor]];
    [self.textView.layer setCornerRadius:30];
    [self.textView setText:@"200"];
    [self.textView setTextAlignment:NSTextAlignmentCenter];
    [self.view addSubview:self.textView];
    
    
    self.textView2 = [[UITextField alloc] initWithFrame:CGRectMake(7, 230, 60, 60)];
    [self.textView2 setBackgroundColor:[UIColor whiteColor]];
    [self.textView2.layer setBorderWidth:3.0];
    [self.textView2.layer setBorderColor:[UIColor blueColor].CGColor];
    [self.textView2 setFont:[UIFont boldSystemFontOfSize:25]];
    [self.textView2 setTextColor:[UIColor blackColor]];
    [self.textView2.layer setCornerRadius:30];
    [self.textView2 setText:@"200"];
    [self.textView2 setTextAlignment:NSTextAlignmentCenter];
    [self.view addSubview:self.textView2];
    [self.carManager registerUIDelegate:self];
 
}

- (void)carNavigationManager:(TNKCarNaviManager *)manager updateNavigationData:(TNKCarNavigationData *)data
{
    [self.textView setText:[[NSString alloc] initWithFormat:@"%i", data.limitSpeed]];
    [self.textView2 setText:[[NSString alloc] initWithFormat:@"%i", data.currentSpeed]];
}

- (void)setupTrafficBarWidget
{
    
    CGFloat trafficBarHeight = [UIScreen mainScreen].bounds.size.height * 0.45;
    TNKNaviTrafficBarWidget *trafficBarWidget = [[TNKNaviTrafficBarWidget alloc] initWithFrame:CGRectMake(self.view.bounds.size.width - 30, (self.view.bounds.size.height - trafficBarHeight) / 2.0, 18, trafficBarHeight)];
    trafficBarWidget.orientation = TNKNaviTrafficBarWidgetOrientationVertical;
    trafficBarWidget.cornerRadius = trafficBarWidget.bounds.size.width / 2.0;
    
    [self.view addSubview:trafficBarWidget];
    [self.carManager registerUIDelegate:trafficBarWidget];
    
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    [self setupPanel];
    [self setupTrafficBarWidget];
    
}

@end
