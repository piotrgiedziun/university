//
//  HomeViewController.h
//  iHome
//
//  Created by Piotr Giedziun on 11/11/13.
//  Copyright (c) 2013 Piotr Giedziun. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface HomeViewController : UITableViewController {
    NSMutableData *responseData;
    MBProgressHUD *hud;
}
    - (IBAction) toggleSwitch: (id) sender;
@end
