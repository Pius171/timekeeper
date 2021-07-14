# timekeeper
The project is about an electronic timekeepers with esp8266. It uses LITTLEFS to store the time and dtime is updated via a webserver 
![Schematic_ESP8266 Timekepper_2021-07-14](https://user-images.githubusercontent.com/70412012/125542620-726b1e41-1a8f-484e-b37a-38a55d39993e.png)

## Home page:
To access the home page of the timekeeper connect to the timekepper via wifi, in your wifi setting you should see a device named timekeeper, the default password is 12345678. then in your browser type in timekeeper.com, you should see the following page when the page loads.
![homePage](https://user-images.githubusercontent.com/70412012/125546310-3106fe1e-254c-42a9-8e95-dd80b7cd90b2.png)

when the time for a particular period has not been set, it shows "not set" but if it has been set it shows the time

To set the time click on tools > Update
![update_click](https://user-images.githubusercontent.com/70412012/125546674-1389bcca-ff41-4709-a094-7e66e3c65a97.png)

After the page has loded you should see this page below
![Update_page](https://user-images.githubusercontent.com/70412012/125546738-f829ac11-93ce-4ea6-9864-639788e3a2e5.png)

From here you can set the time for each period per day, change the password and set date and time of the timekeeper. 

As an example i will update Monday 2nd period which has not been set
![update_click](https://user-images.githubusercontent.com/70412012/125546674-1389bcca-ff41-4709-a094-7e66e3c65a97.png)
as you can see monday second period is at "not set", now let update the time

![updating](https://user-images.githubusercontent.com/70412012/125547169-504c6aeb-af78-483e-bdf8-5df0e5c840f7.png)
after setting the time scroll down and click upload, *it is also possible to set the time for multiple periods before upload*.
After you click uplaod you will be directed to the page below
![saved](https://user-images.githubusercontent.com/70412012/125547641-e047ee3f-40dd-4ad8-b5c6-9a4bf26d372c.png)
Click on Home to go back to the Home page, when you arruve at the Home page you should notice that Monday 2nd period is no longer at "not set", but at the time you set it to.
![after_update](https://user-images.githubusercontent.com/70412012/125547784-99c9cb66-8599-4de6-a9c1-5d5811f645c8.png)

## Deleting periods
To delete a period click on tools > Delete period(s)
![hover_delete](https://user-images.githubusercontent.com/70412012/125548113-f11a1427-f27f-4fce-b80a-6bdcffd2d8cc.png)

Delete page
![delete_page](https://user-images.githubusercontent.com/70412012/125548496-1694e6ac-5054-428a-b241-e0eed9d75d37.png)

We will be deleting Monday 1st period as an example,first look at the time for Monday 1st Period, the time is **8:46**, when we delete it it should default to "not set".
**BEFORE DELETION**
![b4_delete](https://user-images.githubusercontent.com/70412012/125548543-841357aa-ecb2-4fd7-8825-42e8cf8f03d7.png)


![Screenshot from 2021-07-14 02-21-19](https://user-images.githubusercontent.com/70412012/125548638-55aed23d-0c8f-4caa-81f1-f13329bb1ce9.png)

 
![Screenshot from 2021-07-14 02-21-53](https://user-images.githubusercontent.com/70412012/125548674-77ebb42d-94c0-435e-927c-5a9a1974a482.png)

When the page has been deleted go back to the home page by clicking home on the nav bar, you should see that Mon 1st Period is now at "not set"
![mon1stPeriodDeleted](https://user-images.githubusercontent.com/70412012/125549323-c92eab15-2510-4a6a-842a-719abb235310.png)

Lastly to access the user manual or contact page
User manual : click on User manual from nav bar
contact us : tools > contact us

Thanks for reading. I would love it if you give my repo a star, create issues that you discover and make pull requests for any cobtribution you might have.









