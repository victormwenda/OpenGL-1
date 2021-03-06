#include "Floor.h"
#include <windows.h>
#include <gl/gl.h>
#include "Util/GLUtil.h"

bool Floor::_visible = true;
bool Floor::_axisVisible = true;
bool Floor::_gridVisible = false;
bool Floor::_gridLinesVisible = true;

void Floor::SetVisible(bool visible)
{
	_visible = visible;
}

void Floor::SetAxisVisible(bool axisVisible)
{
	_axisVisible = axisVisible;
}

void Floor::SetGridVisible(bool gridVisible)
{
	_gridVisible = gridVisible;
}

void Floor::SetGridLinesVisible(bool gridLinesVisible)
{
	_gridLinesVisible = gridLinesVisible;
}

void Floor::Draw()
{
	if(_visible == false)
		return;

	float lineWidth_bk = glUtil::GLLineWidth(1.0f);
	GLboolean glLighting = glUtil::GLEnable(GL_LIGHTING, false);

	float start = -16;
	float end = 16;
	float gap = 1;

	if(_gridLinesVisible)
	{
		glLineWidth(1.0f);

		glBegin(GL_LINES);
		glColor4ub(255,255,255,60);

		for(int i=(int)start; i<=end; i+=(int)gap)
		{
			glVertex3f(start,	0.01f,	(float)i);
			glVertex3f(end,		0.01f,	(float)i);
		}

		for(int i=(int)start; i<=end; i+=(int)gap)
		{
			glVertex3f((float)i,	0.01f,	start);
			glVertex3f((float)i,	0.01f,	end);
		}
		glEnd();
	}

	if(_axisVisible)
	{
		glLineWidth(3.0f);
		glBegin(GL_LINES);
			glColor4ub(255,0,0,255);
			glVertex3f((start+end)/2.0f, 0.01f, 0.0f);
			glVertex3f(end, 0.01f, 0.0f);

			glColor4ub(0,0,255,255);
			glVertex3f(0,0.01f,(start+end)/2.0f);
			glVertex3f(0,0.01f,end);

			glColor4ub(0,255,0,255);
			glVertex3f(0,0.01f,(start+end)/2.0f);
			glVertex3f(0,end,0);
		glEnd();
	}

	if(_gridVisible)
	{
		glBegin(GL_QUADS);

		int c1 = 255;
		int c2 = 158;
		for(int outer = (int)start; outer < end; outer++)
		{
			int temp = c1;
			c1 = c2;
			c2 = temp;
			for(int i=(int)start; i<end; i+=(int)gap)
			{
				if(i%2 == 0)
					glColor4ub(c1,c2,158,255);
				else
					glColor4ub(c2,c1,158,255);

				glVertex3f((float)i,		0, outer*gap);
				glVertex3f((float)i+gap,	0, outer*gap);
				glVertex3f((float)i+gap,	0, (outer+1)*gap);
				glVertex3f((float)i,		0, (outer+1)*gap);
			}
		}
		glEnd();

		/*
		glColor4ub(255,255,255,255);
		glBegin(GL_TRIANGLES);
			glVertex3f(start,0,start);
			glVertex3f(start,0,end);
			glVertex3f(end,0,end);
			glVertex3f(start,0,start);
			glVertex3f(end,0,end);
			glVertex3f(end,0,start);
		glEnd();
		*/
	}

	glUtil::GLLineWidth(lineWidth_bk);
	glUtil::GLEnable(GL_LIGHTING, glLighting);
}
