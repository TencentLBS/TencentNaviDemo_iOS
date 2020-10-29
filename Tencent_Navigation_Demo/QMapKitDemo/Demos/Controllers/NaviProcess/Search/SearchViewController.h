//
//  SearchViewController.h
//  NavigationDemo
//
//  Created by xue on 2018/1/15.
//  Copyright © 2018年 xue. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import <QMapKit/QMSSearchKit.h>

typedef NS_ENUM(NSUInteger, PointSearchType) {
    PointSearchType_Start,          //起始点搜索
    PointSearchType_Destination,    //目的地搜索
    PointSearchType_WayPoint,       //途经点搜索
};


NS_ASSUME_NONNULL_BEGIN

@class SearchViewController;

@protocol SearchViewControllerDelegate <NSObject>

- (void)searchViewController:(SearchViewController *)searchViewController
    didSuccessSearchWithData:(QMSSuggestionPoiData *)data;

- (void)searchViewController:(SearchViewController *)searchViewController
      didFailSearchWithError:(NSError *)error;

@end

@protocol SearchViewControllerDataSource <NSObject>

- (CLLocation *)searchViewControllerStartLocationForSearchRequest:(SearchViewController *)searchViewController;

@end

@interface SearchViewController : UIViewController

@property (nonatomic, weak) id<SearchViewControllerDelegate> delegate;
@property (nonatomic, weak) id<SearchViewControllerDataSource> dataSource;
@property (nonatomic, strong, nullable) NSString *placeholderString;
@property (nonatomic, strong) NSMutableArray *searchHistories;
@property (nonatomic, assign) PointSearchType pointSearchType;

@end

NS_ASSUME_NONNULL_END

