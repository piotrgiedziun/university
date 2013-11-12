//
//  SecondViewController.h
//  iHome
//
//  Created by Piotr Giedziun on 11/5/13.
//  Copyright (c) 2013 Piotr Giedziun. All rights reserved.
//
#import <CoreLocation/CoreLocation.h>
#import "MBProgressHUD.h"
#import <UIKit/UIKit.h>

@interface SecondViewController : UIViewController <CLLocationManagerDelegate> {
    NSMutableData *responseData;
    MBProgressHUD *hud;
}
@property (strong, nonatomic) IBOutlet UIDatePicker *datePicker;
- (IBAction) toggleSwitch: (id) sender;
@end
