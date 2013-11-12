//
//  SecondViewController.m
//  iHome
//
//  Created by Piotr Giedziun on 11/5/13.
//  Copyright (c) 2013 Piotr Giedziun. All rights reserved.
//

#import "SecondViewController.h"
#import "MBProgressHUD.h"
#import "statics.h"

@interface SecondViewController ()

@end

@implementation SecondViewController

CLLocationManager *locationManager;

- (void)request: (NSString *)url
{
    NSURL *myURL = [NSURL URLWithString:[NSString stringWithFormat:@"%@%@", API_URL, url]];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:myURL
                                                           cachePolicy:NSURLRequestReloadIgnoringLocalCacheData timeoutInterval:60];
    
    [[NSURLConnection alloc] initWithRequest:request delegate:self];
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
    responseData = [[NSMutableData alloc] init];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    [responseData appendData:data];
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
    [self hideProgressBar];
    UIAlertView *errorAlert = [[UIAlertView alloc]
                               initWithTitle:@"Error" message:@"Request timeout" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [errorAlert show];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    [self hideProgressBar];
    NSLog(@"Succeeded! Received %d bytes of data",[responseData length]);
    
    NSString *txt = [[NSString alloc] initWithData:responseData encoding: NSASCIIStringEncoding];
    
}

- (void)showProgressBar
{
    hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    hud.labelText = @"Loading..";
    [hud show:YES];
}

- (void)hideProgressBar
{
    [hud hide:YES];
}

- (IBAction) toggleSwitch: (id) sender {
    UISwitch *onoff = (UISwitch *) sender;
    if ( onoff.tag == 1) {
        // location based
        if(onoff.on) {
            // power on
            locationManager.delegate = self;
            locationManager.desiredAccuracy = kCLLocationAccuracyBest;
            
            [locationManager startUpdatingLocation];
        }else{
            // power off
            [locationManager stopUpdatingLocation];
        }
        
    }else{
        // time based
        if(onoff.on) {
            // get time
            _datePicker.hidden = FALSE;
            NSDateFormatter* formatter = [[NSDateFormatter alloc] init];
            [formatter setDateFormat:@"hh/mm"];
            NSLog (@"Date %@", [formatter stringFromDate:_datePicker.date]);
            [self request:[NSString stringWithFormat:@"time/%@", [formatter stringFromDate:_datePicker.date]]];
        }else{
            [self request:@"time/off"];
            // hide
            _datePicker.hidden = TRUE;
        }
    }
}
#pragma mark - CLLocationManagerDelegate

- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error
{
    NSLog(@"didFailWithError: %@", error);
    UIAlertView *errorAlert = [[UIAlertView alloc]
                               initWithTitle:@"Error" message:@"Failed to Get Your Location" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [errorAlert show];
}

- (void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation
{
    NSLog(@"didUpdateToLocation: %@", newLocation);
    CLLocation *currentLocation = newLocation;
    
    if (currentLocation != nil) {
        // send location...
        [self request:[NSString stringWithFormat:@"location/%.4f/%.4f", currentLocation.coordinate.longitude, currentLocation.coordinate.latitude]];
        NSLog(@"%.4f %.4f",currentLocation.coordinate.longitude, currentLocation.coordinate.latitude);
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    locationManager = [[CLLocationManager alloc] init];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
