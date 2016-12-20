#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>

namespace gazebo
{
  class ModelPush : public ModelPlugin
  {
    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
    {
      // Store the pointer to the model
      this->model = _parent;

      // Listen to the update event. This event is broadcast every
      // simulation iteration.
      this->updateConnection = event::Events::ConnectWorldUpdateBegin(
          boost::bind(&ModelPush::OnUpdate, this, _1));

      this->model->SetLinearVel(math::Vector3(0.1, 0.09, 0));
    }

    // Called by the world update start event
    public: void OnUpdate(const common::UpdateInfo & /*_info*/)
    {
      // Apply a small linear velocity to the model.
//      this->model->SetLinearVel(math::Vector3(.03, 0.05, 0));
        check_key_command();
    }

    // Pointer to the model
    private: physics::ModelPtr model;

    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;

/////////////////////////////////////////////////
// To know pushing any key
int	doslike_kbhit(void)
{
	struct termios	oldt, newt;
	int	ch;
	int	oldf;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(BRKINT | ISTRIP | IXON);
	newt.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	if(ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}
	return 0;
}

/////////////////////////////////////////////////
// To gwt a charactor code of a pushed key
int	doslike_getch(void)
{
	static struct termios	oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(BRKINT | ISTRIP | IXON);
	newt.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	int c = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return c;
}

/////////////////////////////////////////////////
// To control joint behaviors by keyboard input directory
void	check_key_command(void)
{
	if(doslike_kbhit())
	{
		int cmd = doslike_getch();
		switch(cmd)
		{
			case 'i': this->model->SetLinearVel(math::Vector3(0, 0.1, 0));
				  break;
			case 'j': this->model->SetLinearVel(math::Vector3(-0.1, 0, 0));
				  break;
			case 'l': this->model->SetLinearVel(math::Vector3(0.1, 0, 0));
				  break;
			case ',': this->model->SetLinearVel(math::Vector3(0, -0.1, 0));
				  break;
			case 'k': this->model->SetLinearVel(math::Vector3(0, 0, 0));
				  break;
		}
	}
}

  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(ModelPush)
}
