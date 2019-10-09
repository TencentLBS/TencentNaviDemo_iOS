//
//  CustomNaviController.m
//  QMapKitDemo
//
//  Created by Tencent on 2018/8/8.
//  Copyright © 2018年 tencent. All rights reserved.
//

#import "CustomNaviController.h"

@interface CustomNaviController()
@property(nonatomic, strong) UITextView *textView;
@property(nonatomic, strong) UIImageView *imageView;
@property(nonatomic, strong) UITextView *textView2;
@end

@implementation CustomNaviController

- (void)setupPanel
{
    self.naviView.hideNavigationPanel = YES;
    
    UIView* backgroundTitleView = [[UIView alloc] initWithFrame:CGRectMake(self.naviView.frame.size.width / 2 - 200, 7, 400, 100)];
    backgroundTitleView.backgroundColor = [UIColor blackColor];
    backgroundTitleView.alpha = 0.8;
    backgroundTitleView.layer.cornerRadius = 15;
    [self.naviView addSubview:backgroundTitleView];
    
    self.textView = [[UITextView alloc] initWithFrame:CGRectMake(30, 30, 90, 70)];
    [self.textView setBackgroundColor:[UIColor clearColor]];
    [self.textView setFont:[UIFont boldSystemFontOfSize:20]];
    [self.textView setTextColor:[UIColor whiteColor]];
    [self.textView setTextAlignment:NSTextAlignmentCenter];
    [self.textView setText:@"200米后"];
    [backgroundTitleView addSubview:self.textView];
    
    
    self.imageView = [[UIImageView alloc] initWithFrame:CGRectMake(130, 25, 50, 50)];
    [self.imageView setBackgroundColor:[UIColor clearColor]];
    self.imageView.contentMode = UIViewContentModeScaleAspectFit;
    self.imageView.clipsToBounds = YES;
    [backgroundTitleView addSubview:self.imageView];
    
    self.textView2 = [[UITextView alloc] initWithFrame:CGRectMake(200, 30, 170, 70)];
    [self.textView2 setBackgroundColor:[UIColor clearColor]];
    [self.textView2 setTextColor:[UIColor whiteColor]];
    [self.textView2 setFont:[UIFont boldSystemFontOfSize:20]];
    [self.textView2 setTextAlignment:NSTextAlignmentCenter];
    
    [self.textView2 setText:@"到达苏州街"];
    [backgroundTitleView addSubview:self.textView2];
    
//    [self.carManager registerUIDelegate:self];
}

- (NSString*)formatDis:(NSInteger)dis
{
    if(dis >= 1000)
    {
        return [[NSString alloc] initWithFormat:@"%f公里后", dis / 1000.0];
    } else {
        return [[NSString alloc] initWithFormat:@"%i 米后", (int)dis];
    }
}

- (void)carNavigationManager:(TNKCarNaviManager *)manager updateNavigationData:(TNKCarNavigationData *)data
{
    [self.textView setText:[[NSString alloc] initWithFormat:@"%@%@后", data.nextDistanceLeftString, data.nextDistanceLeftUnit]];
    [self.textView2 setText:[[NSString alloc] initWithFormat:@"到达%@", data.nextRoadName]];
    [self.imageView setImage:data.intersectionImage];
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    [self setupPanel];
    
}


@end
