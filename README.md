# README.md
Welcome to the CIS 330 Final Project Game Repository.
Please read this entire document every time you see a change to it.

### Rules of the repository.
* When to use branches:
    1. Only commit _FINAL_ code to the `master` branch, generally you will be committing into another branch and merging both branches together. **AVOID DIRECTLY COMMITTING TO MASTER BRANCH**
    1. Use a branch off of the `master` branch if there is a specific feature set that is being added but not ready completed. 
        1. Submit a pull request (PR) to merge the master branch and the specific branch when you think the feature is completed. 
        1. Then the team will review the PR and approve it after determining if the code is stable.

* When to create a new branch, and what to use for the parent branch.
    1. When do you want to create a new branch?
        1. When you assign a specific person to a task in asana.
            * You will want to use the `CH-([0-9]+)` number as the name of the branch and generally create it off the most recent `master` branch commit (This will ensure that all previous completed code is included in your branch, any future code on the master branch will not be included).
            **Please ensure that you are following the template in asana for assigning code work to _yourself_ or _each other_ as we need to be consistent and understandable.**
        1. If there is not already a branch that contains code related to the feature set.
            * There should be discussion in asana before this happens see the above section a).
        1. If there is a distinctly different set of code that needs to be written in isolation to other code.
            * There should be discussion in asana before this happens see the above section a).
### When to commit to this repository 
What code should I commit to this repository.
1. Commit working code as you do it, as close to realtime as possible. **Ensure that the realtime code goes into the branch that directly relates to the work. _this ensures codebase consistency_**
1. When you think you have completed work on a branch then go ahead and submit a Pull Request (PR) to merge the branch, `CH-([0-9]+)`, into the `master` branch so that we can all share in the glory.

Thanks and happy coding!