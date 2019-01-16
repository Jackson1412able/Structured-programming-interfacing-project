/* 
    The program was written in C programming language. The program prompts user for current
    , resistance, inductance and capacitance measurements. The system then generates 200 pseudo-random
    frequency inputs and calculate impedance and voltage based on the generated frequencies. The voltages
    will then be plotted in a web page and the maximum and minimum voltages are indicated in the plot.
    The C program was written to generate the design of the web page using HTML and CSS.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi 3.14159265359
#define size 200

float calculations(float Current, float Resistance, float Capacitance_uF, float Inductance_mH); // function definitions//
float MaxMin_voltage_current(float voltages[], float currents[], float impedances[], float REsistance, float capacitance_microF, float inductance_milliH, float Frequency[]);
void output(float VOLTAGES[], float CURRENTS[], float maxV, float minV, float maxI, float minI, float IMPEDANCES[], float RESISTANCE, float CAPACITANCE_uF, float INDUCTANCE_mH, float FREQUENCY[]);

/*------------------------------------------- Main Program --------------------------------------------------*/

void main()
{
  float current, resistance, capacitance_uF, inductance_mH; // Variables for current, resistance, capacitance and inductance //

  printf("This program calculates the resistance/impedance of a R/RL/RC/RLC circuit.\n");
  printf("This program also generates 200 random frequency values ranged from 25-50Hz and output the voltages to a HTML file and display the voltages in a tabulated form and also a graph of it.\n");
  printf("Please enter the following values:\n");
  printf("Current(A):");
  scanf("%f", &current);
  printf("Resistance(Ohms):");
  scanf("%f", &resistance);
  printf("Capacitance(micro Farad):");
  scanf("%f", &capacitance_uF);
  printf("Inductance(milli Henry):");
  scanf("%f", &inductance_mH);
  
  printf("\nGenerating random frequency values...\n");
  calculations(current, resistance, capacitance_uF, inductance_mH); //function for value processing//
}

/*-------------- Calculate current, frequency, capacitive reactance, inductive reactance, impedance and voltage values -------------------------------------*/

void calculations(float Current, float Resistance, float Capacitance_uF, float Inductance_mH) 
{
  float Capacitance, Inductance, frequency[size], impedance[size], voltage[size], CURRENT[size], capacitive_reactance, inductive_reactance;
  int i;
  Capacitance = Capacitance_uF / 1000000;
  Inductance = Inductance_mH / 1000;

  for(i=0;i<size;i++) // Calculation of values //
  {
    CURRENT[i] = Current;
    frequency[i] = 25 + 25*((float)rand()/RAND_MAX);
    capacitive_reactance = 1/2/pi/frequency[i]/Capacitance;
    inductive_reactance = 2*pi*frequency[i]*Inductance;
    impedance[i] = sqrt((Resistance*Resistance)+((inductive_reactance-capacitive_reactance)*(inductive_reactance-capacitive_reactance)));
    voltage[i] = CURRENT[i]*impedance[i];
  }

  MaxMin_voltage_current(voltage, CURRENT, impedance, Resistance, Capacitance_uF, Inductance_mH, frequency); //function for determining maximum and minimum voltage and current//
}

/*--------------------------------- Determining maximum and minimum voltage and currents ---------------------------------*/

void MaxMin_voltage_current(float voltages[], float currents[], float impedances[], float REsistance, float capacitance_microF, float inductance_milliH, float Frequency[])
{
  float max_voltage, min_voltage, max_current, min_current;
  int index;
  max_voltage = 0;
  min_voltage = voltages[0];
  max_current = 0;
  min_current = currents[0];

  for(index=0;index<size; index++) //determining maximum and minimum voltage and current//
  {
    if(voltages[index]>max_voltage)
    max_voltage = voltages[index];

    if(currents[index]>max_current)
    max_current = currents[index];

    if(voltages[index]<min_voltage)
    min_voltage = voltages[index];

    if(currents[index]<min_current)
    min_current = currents[index];
  }

  output(voltages, currents, max_voltage, min_voltage, max_current, min_current, impedances, REsistance, capacitance_microF, inductance_milliH, Frequency); //function for writing the data to a html file//
}

/*-------------------------------------------------- Displaying the results in a web page --------------------------------------------------*/

void output(float VOLTAGES[], float CURRENTS[], float maxV, float minV, float maxI, float minI, float IMPEDANCES[], float RESISTANCE, float CAPACITANCE_uF, float INDUCTANCE_mH, float FREQUENCY[])
{
  FILE *fp; //file pointer//
  char file[] = "volt20128.html"; //html file name//
  int count, i1, i2, currentAxis, i3, i4, voltageAxis;
  fp = fopen(file, "w"); //open file for writing access//

  if (fp == NULL) //condition if file is unable to open//
  {
    printf("Unable to access to file \"%s\"\n", file);
    exit(1);
  }

  printf("Writing data to \"%s\"...\n", file);
  
  /*--------------------------------------------------writing html attributes--------------------------------------------*/
  fprintf(fp, "<!DOCTYPE html>\n");
  fprintf(fp, "<html>\n");
  fprintf(fp, "<style>\n");
  fprintf(fp, "body {background-image: url(\"http://www.ipad-hd-wallpapers.com/abstract-lighttexture-wallpaper-for-ipad-2,2560x1920,ipad-3-wallpaper,342.jpg\");\n");
  fprintf(fp, "background-repeat: no-repeat;\n");
  fprintf(fp, "background-attachment: fixed;}\n");
  fprintf(fp, "h1 {text-align:center; text-shadow: 3px 3px 3px #585858}\n");
  fprintf(fp, "table {visibility: collapse;}\n");
  fprintf(fp, "th {background-color: #383838; color: white;}\n");
  fprintf(fp, "td {text-align:center;}\n");
  fprintf(fp, "#div1 { float:right; width 40px; height 25px; font-family:Times New Roman; padding: 20px; border-radius: 10px; border: 10px solid #909090;}\n");
  fprintf(fp, "div2 { width:150px; height:80px; -webkit-transition: width 2s, height 2s; transition:width 2s, height 2s, font-size 2s; font-size:0px;}");
  fprintf(fp, "#div2 { float:left; width 40px; height 25px; font-family:Times New Roman; padding: 20px; border-radius: 10px; border: 10px solid #707070;}\n");
  fprintf(fp, "div2:hover {width:%fpx; height:9550px; font-size:20px;}", 300+maxV/5);
  fprintf(fp, "</style>\n");
  fprintf(fp, "<h1>RLC circuit values</h1><br>\n"); //html header text//
  fprintf(fp, "<p>Table for the RLC circuit values\n");
  fprintf(fp, "<script>\nfunction hideTable(){document.getElementById('table').style.visibility = \"collapse\";}\n");
  fprintf(fp, "function showTable(){\ndocument.getElementById('table').style.visibility = \"visible\";}\n</script>");
  fprintf(fp, "<body onload=\"javascript:hideTable()\">\n");
  fprintf(fp, "<input type='button'\nonClick='javascript:showTable();'value='show'>\n");
  fprintf(fp, "<input type='button'\nonClick='javascript:hideTable();'value='hide'>\n");
  fprintf(fp, "<table id='table' border=7>\n");
  fprintf(fp, "<tr><br>\n");
  fprintf(fp, "<th>Measurement</th><th>Current(A)</th><th>Resistance(Ohm)</th><th>Capacitance(uF)</th><th>Inductance(mH)</th><th>Frequency(Hz)</th><th>Impedance(Ohm)</th><th>Voltage(V)</th></tr>\n");

  for (count=0;count<size;count++)
  {
    fprintf(fp, "<tr><td>%12d<td>%7.2f</td> <td>%10.2f</td> <td>%14.2f</td> <td>%13.2f</td> <td>%11.2f</td> <td>%12.2f</td> <td>%10.2f</td></tr>\n", count+1, CURRENTS[count], RESISTANCE,CAPACITANCE_uF, INDUCTANCE_mH, FREQUENCY[count], IMPEDANCES[count], VOLTAGES[count]);
  }
  fprintf(fp, "</table>\n");
  fprintf(fp, "<div id=\"div1\"><ul>");
  fprintf(fp, "<font size =\"5\"><b>Maximum and minimum values</b></font><br>\n");
  fprintf(fp, "<li>The minimum current is %.2fA.</li>\n", minI);
  fprintf(fp, "<li>The maximum current is %.2fA.</li>\n", maxI);
  fprintf(fp, "<li>The minimum voltage is %.2fV.</li>\n", minV);
  fprintf(fp, "<li>The maximum voltage is %.2fV.</li>\n", maxV);
  fprintf(fp, "</ul></div>\n"); 
  fprintf(fp, "<div2 id=\"div2\">");
  fprintf(fp, "<br>&nbsp;&nbsp;&nbsp;&nbsp;<font size=\"4\"><b>Graph for current</b></font><br><br>\n");
  fprintf(fp, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;.\n"); 

  for(currentAxis=0; currentAxis<(maxI+2); currentAxis++)
    fprintf(fp, "_");

  fprintf(fp, "Current<br>\n");

  for(i1=0; i1<size; i1++)
  {
    fprintf(fp, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|");
    for(i2=0; i2<CURRENTS[i1]; i2++)
    fprintf(fp, "-");
    fprintf(fp, "*<br>\n");
  }

  fprintf(fp, " Measurement<br>\n");
  fprintf(fp, "<br>&nbsp;<font size=\"4\"><b>Graph for voltage</b></font><br><br>\n");File: /home/jackson/a5LJH20128.c Page 4 of 4
  fprintf(fp, "Legends:");
  fprintf(fp, "<ul><li>Maximum voltage +</li><li>Minimum voltage -</li></ul>");
  fprintf(fp, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;.");
  for(voltageAxis=0; voltageAxis<((maxV/50)+10); voltageAxis++)
  fprintf(fp, "_");
  fprintf(fp, "Voltage<br>\n");

  for(i3=0; i3<size; i3++)
  {
    fprintf(fp, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|");
    for(i4=0; i4<(VOLTAGES[i3]/50); i4++)
    fprintf(fp, "-");
    
    if(VOLTAGES[i3]==minV)
      fprintf(fp, "*&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-<br>\n");
    else if (VOLTAGES[i3]==maxV)
      fprintf(fp, "*&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;+<br>\n");
    else
      fprintf(fp, "*<br>\n");
  }

  fprintf(fp, " &nbsp;&nbsp;Measurement<br>\n");
  fprintf(fp, "<font size=\"3\"><em>Move cursor to here to view the graphs</em></font>");
  fprintf(fp, "</div>");
  fprintf(fp, "<br>\n");
  fprintf(fp, "</p>\n");
  fprintf(fp, "</body>\n");
  fprintf(fp, "</html>\n");
  printf("Writing data completed. The file \"%s\" can be opened now.\n", file);
  fclose(fp);
 }
