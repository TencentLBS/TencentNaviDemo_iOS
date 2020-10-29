//
//  NavigationViewController.h
//  TNKNavigation
//
//  Created by tabsong on 2018/4/12.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import <UIKit/UIKit.h>


@class NavigationViewController, TNKCarNaviManager;

@protocol NavigationViewControllerDelegate <NSObject>

- (void)navigationViewControllerDidStop:(NavigationViewController *)navigationViewController;

@end

@interface NavigationViewController : UIViewController

- (instancetype)initWithCarNaviManager:(TNKCarNaviManager *)carNaviManager routeIndex:(NSUInteger)routeIndex simulateLocation:(BOOL)simulation;

@property (nonatomic, weak) id <NavigationViewControllerDelegate> delegate;

@end
