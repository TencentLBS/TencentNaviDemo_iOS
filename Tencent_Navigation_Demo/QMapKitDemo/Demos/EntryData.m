//
//  EntryData.m
//  QMapKitDemoNew
//
//  Created by Tencent on 17/5/11.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "EntryData.h"
#import <QMapKit/QMapKit.h>

@implementation Cell

@end

@implementation Section

@end

@implementation EntryData

+ (instancetype)constructDefaultEntryData
{
    EntryData *entry = [[EntryData alloc] init];
    entry.title = @"Navigation Demo";
    NSMutableArray<Section *> *sectionArray = [NSMutableArray array];
    entry.sections = sectionArray;
    

    {
        Section *section = [[Section alloc] init];
        section.title = @"导航全流程";
        NSMutableArray<Cell *> *cellArray = [NSMutableArray array];
        section.cells = cellArray;
    
        [sectionArray addObject:section];
        
        // 基础导航
        {
            Cell *cell = [[Cell alloc] init];
            cell.title = @"导航全流程";
            cell.controllerClassName = @"CarPlanController";
            [cellArray addObject:cell];
        }
    }
    
    // Navi Section.
    {
        Section *section = [[Section alloc] init];
        section.title = @"基础导航";
        NSMutableArray<Cell *> *cellArray = [NSMutableArray array];
        section.cells = cellArray;
    
        [sectionArray addObject:section];
        
        // 基础导航
        {
            Cell *cell = [[Cell alloc] init];
            cell.title = @"导航算路";
            cell.controllerClassName = @"NaviSearchRoutes";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"实时导航";
            cell.controllerClassName = @"RealNaviController";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"模拟导航";
            cell.controllerClassName = @"SimuNaviController";
            [cellArray addObject:cell];
            
        }
    }
    
    {
        Section *section = [[Section alloc] init];
        section.title = @"导航设置配置";
        NSMutableArray<Cell *> *cellArray = [NSMutableArray array];
        section.cells = cellArray;
        
        [sectionArray addObject:section];
        
        {
            Cell *cell = [[Cell alloc] init];
            cell.title = @"设置导航模式";
            cell.controllerClassName = @"NaviModeController";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"设置日夜功能";
            cell.controllerClassName = @"NaviDayNightController";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"设置路线宽度";
            cell.controllerClassName = @"NaviRouteWidthController";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"设置路况线颜色";
            cell.controllerClassName = @"NaviRouteColorViewController";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"设置路况箭头间隔";
            cell.controllerClassName = @"NaviRouteSymbolGapViewController";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"设置自动缩放比例尺";
            cell.controllerClassName = @"AutoScaleViewController";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"设置自车点罗盘";
            cell.controllerClassName = @"NaviCustomCarCompassViewController";
            [cellArray addObject:cell];
        }
    }
    
    {
        Section *section = [[Section alloc] init];
        section.title = @"自定义UI";
        NSMutableArray<Cell *> *cellArray = [NSMutableArray array];
        section.cells = cellArray;
        
        [sectionArray addObject:section];
        

        {
            Cell *cell = [[Cell alloc] init];
            cell.title = @"默认导航面板";
            cell.controllerClassName = @"DefaultNaviController";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"自定义导航面板";
            cell.controllerClassName = @"CustomNaviController";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"添加控件";
            cell.controllerClassName = @"AddKitNaviController";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"添加地图控件";
            cell.controllerClassName = @"AddMapKitNaviController";
            [cellArray addObject:cell];

        }
    }
    
    {
        Section *section = [[Section alloc] init];
        section.title = @"步骑行导航";
        NSMutableArray<Cell *> *cellArray = [NSMutableArray array];
        section.cells = cellArray;
        
        [sectionArray addObject:section];
        {
            Cell *cell = [[Cell alloc] init];
            cell.title = @"步行导航";
            cell.controllerClassName = @"WalkNaviViewController";
            [cellArray addObject:cell];
            
            cell = [[Cell alloc] init];
            cell.title = @"骑行导航";
            cell.controllerClassName = @"RideNaviViewController";
            [cellArray addObject:cell];
        }
    }
    
    return entry;
}

@end
