#include<iostream>
#include<omp.h>
#include<vector>
#include<random>
#include<math.h>
#include"test_func.h"
using namespace std;



class Particle
{
  private :
    vector <double> velocity;
    vector <double> particle_best_position;
    vector <double> position;
    double particle_error;
    double best_error;

  public :
    friend class PSO;

    Particle(int dim, vector <double> rangemin, vector <double> rangemax)
    {
      for( int i=0; i<dim; i++)
      {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(rangemin[i],rangemax[i]);  
        position.push_back(dis(gen));
        particle_best_position.push_back(2);

        velocity.push_back(0);
      }

    }
    

};

class PSO
{
  private :
    int population;
    int dimension;
    int steps;
    vector <Particle> particles;
    double group_best;
    vector <double> group_best_pos;
    double c1,c2;        //acceleration coefficents
    vector<double> rangemax;
    vector<double> rangemin;
    double inertia = 0.7; 

  public :

    void init(int pop,vector<double> spacemin,vector<double> spacemax,double C1,double C2,int s)
    {
      population = pop;
      dimension = spacemax.size();
      rangemin = spacemin;
      rangemax = spacemax;
      for(int i=0;i<dimension;i++)
        group_best_pos.push_back(0);
      c1 = C1;
      c2 = C2 ;
      steps = s;
    }

    void optimize(double (*costFunc)(vector<double> ) )
    {
      vector <double> hi({2,2});
      group_best = costFunc(hi);
      random_device rd;
      mt19937 gen(rd());
      uniform_real_distribution<> dis(0.0,1.0);
  //    #pragma omp parallel for 
      for (int i =0; i<population; i++)
      {
         Particle P(dimension,rangemin,rangemax);
         particles.push_back(P);
      }

      for (int i=0; i<steps; i++)
      {
        #pragma omp parallel for 
        for(int j=0; j<population; j++)
        {

          double curr_cost = costFunc(particles[j].position);

          if(curr_cost <= particles[j].best_error || i==0)
            {
              particles[j].best_error = curr_cost;
              particles[j].particle_best_position = particles[j].position;
            }

          if(curr_cost <= group_best )
            {
              group_best = curr_cost;
              group_best_pos = particles[j].position;
            }
          

          double r1 = dis(gen);
          double r2 = dis(gen);
          vector <double> diff1;
          vector <double> diff2;


          for(int k = 0;k<dimension ;k++)
          {
            diff1.push_back(- particles[j].position[k] + particles[j].particle_best_position[k]);
            diff2.push_back(- particles[j].position[k] + group_best_pos[k]);
            particles[j].velocity[k] = particles[j].velocity[k]*inertia + r1 * c1 * diff1[k] + r2 * c2 * diff2[k];
            particles[j].position[k] += particles[j].velocity[k];
          }

        }

      for(int k=0;k<population;k++)
      { 
        cout << particles[k].position[0] << "\t" << particles[k].position[1]<<"\t";
      
      
      }
      cout << group_best_pos[0] << "\t" << group_best_pos[1]<<"\t";
      
      }
    

    }
    



};





int main()
{
  PSO p;  
  vector<double> max({30,30});
  vector<double> min({-30,-30});
  double population = 3;
  cout << population<<"\n" ; // for visualisation
  p.init( population,min,max,0.03,0.03,50000);

  p.optimize(sphere);


}
