<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->



<h3 align="center">Arduino Based Weather Station</h3>

  <p align="center">
    Hi, this is a project that was inspired when my school bought a weather station, and thinking of ways I could improve it. It is a weather station that uses an Arduino R4 Wifi and some sensors.
    It uses I2C communication for the sensors and OLED screen, and SPI for the data logger. It is fully written in Arduino C++, and the code can be found at     weatherstation.ino
    This is the second version of the weather station, with additional features. 
    <br />
    <a href="https://github.com/muffnpy/weatherstation"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/muffnpy/weatherstation">View Demo</a>
    ·
    <a href="https://github.com/muffnpy/weatherstation/issues">Report Bug</a>
    ·
    <a href="https://github.com/muffnpy/weatherstation/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
      </ul>
    </li>
    <li>
      <ul>
        <li><a href="#prerequisites">Required Libraries</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>




### Required Libraries and Materials

Here are the requried materials and sensors for this project

  ```sh
Required Materials/Sensors:
1 x MicroSD card breakout board = $7.50
1 x Analog UV Light Sensor Breakout - GUVA-S12SD = $6.50
1 x Adafruit AHT20 - Temperature and Humidity Sensor Breakout Board = $4.50
1 x Adafruit BMP388 - Precision Barometric Pressure and Altimeter = $9.95
1 x Adafruit STEMMA Soil Sensor - I2C Capacitive Moisture Sensor = $7.50
1 x Adafruit INA260 High or Low Side Voltage, Current, Power Sensor = $9.95

Optional:
1 x Anemometer Wind Speed Sensor w/Analog Voltage Output = $14.95
1 x Monochrome 0.96 128x64 OLED Graphic Display = $14.50


Requried Libraries:
<Wire.h>
<Adafruit_GFX.h>
<Adafruit_BMP3XX.h>
<Adafruit_AHTX0.h>
<Adafruit_INA260.h>
<WiFiS3.h>
<Adafruit_SSD1306.h>
<SPI.h>
<SD.h>
<RTC.h>
  ```


<!-- ROADMAP -->
## Roadmap

- [ ] Solar rechargable battery system
- [ ] In-house data graphing with TensorFlow
- [ ] User customization options

See the [open issues](https://github.com/github_username/repo_name/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch 
3. Commit your Changes 
4. Push to the Branch 
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Email Me - adenine@adeninelabs.com

Project Link: [https://github.com/github_username/repo_name](https://github.com/muffnpy/weatherstation)

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/github_username/repo_name.svg?style=for-the-badge
[contributors-url]: https://github.com/github_username/repo_name/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/github_username/repo_name.svg?style=for-the-badge
[forks-url]: https://github.com/github_username/repo_name/network/members
[stars-shield]: https://img.shields.io/github/stars/github_username/repo_name.svg?style=for-the-badge
[stars-url]: https://github.com/github_username/repo_name/stargazers
[issues-shield]: https://img.shields.io/github/issues/github_username/repo_name.svg?style=for-the-badge
[issues-url]: https://github.com/github_username/repo_name/issues
[license-shield]: https://img.shields.io/github/license/github_username/repo_name.svg?style=for-the-badge
[license-url]: https://github.com/github_username/repo_name/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/linkedin_username
[product-screenshot]: images/screenshot.png
[Next.js]: https://img.shields.io/badge/next.js-000000?style=for-the-badge&logo=nextdotjs&logoColor=white
[Next-url]: https://nextjs.org/
[React.js]: https://img.shields.io/badge/React-20232A?style=for-the-badge&logo=react&logoColor=61DAFB
[React-url]: https://reactjs.org/
[Vue.js]: https://img.shields.io/badge/Vue.js-35495E?style=for-the-badge&logo=vuedotjs&logoColor=4FC08D
[Vue-url]: https://vuejs.org/
[Angular.io]: https://img.shields.io/badge/Angular-DD0031?style=for-the-badge&logo=angular&logoColor=white
[Angular-url]: https://angular.io/
[Svelte.dev]: https://img.shields.io/badge/Svelte-4A4A55?style=for-the-badge&logo=svelte&logoColor=FF3E00
[Svelte-url]: https://svelte.dev/
[Laravel.com]: https://img.shields.io/badge/Laravel-FF2D20?style=for-the-badge&logo=laravel&logoColor=white
[Laravel-url]: https://laravel.com
[Bootstrap.com]: https://img.shields.io/badge/Bootstrap-563D7C?style=for-the-badge&logo=bootstrap&logoColor=white
[Bootstrap-url]: https://getbootstrap.com
[JQuery.com]: https://img.shields.io/badge/jQuery-0769AD?style=for-the-badge&logo=jquery&logoColor=white
[JQuery-url]: https://jquery.com 
 
