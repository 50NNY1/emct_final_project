#include <vector>
#include <cmath>

class EuclideanSequence
{
public:
    EuclideanSequence(int steps, int pulses, int bpm) : steps_(steps), pulses_(pulses), bpm_(bpm)
    {
        beat_duration_ = 60.0 / bpm_;
    }

    std::vector<int> generateSequence()
    {
        std::vector<int> sequence;
        int gcd_value = gcd(steps_, pulses_);
        int lcm_value = lcm(steps_, pulses_);
        int gap = lcm_value / steps_;
        int remainder = pulses_;

        for (int i = 0; i < steps_; i++)
        {
            int count = gap;
            while (count > 0)
            {
                sequence.push_back(1);
                count--;
                remainder--;
                if (remainder == 0)
                {
                    break;
                }
            }
            if (remainder == 0)
            {
                break;
            }
            sequence.push_back(0);
        }

        return sequence;
    }

    std::vector<float> generateDurations()
    {
        std::vector<float> durations;
        int gcd_value = gcd(steps_, pulses_);
        int lcm_value = lcm(steps_, pulses_);
        int gap = lcm_value / steps_;
        int remainder = pulses_;
        float duration;

        for (int i = 0; i < steps_; i++)
        {
            int count = gap;
            duration = beat_duration_ * gap;
            while (count > 0)
            {
                durations.push_back(duration);
                count--;
                remainder--;
                if (remainder == 0)
                {
                    break;
                }
            }
            if (remainder == 0)
            {
                break;
            }
            durations.push_back(0.0);
        }

        return durations;
    }

private:
    int steps_;
    int pulses_;
    int bpm_;
    float beat_duration_;

    int gcd(int a, int b)
    {
        if (b == 0)
        {
            return a;
        }
        else
        {
            return gcd(b, a % b);
        }
    }

    int lcm(int a, int b)
    {
        return (a * b) / gcd(a, b);
    }
};
